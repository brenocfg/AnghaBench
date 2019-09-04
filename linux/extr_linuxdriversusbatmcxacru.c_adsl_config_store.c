#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct cxacru_data {int /*<<< orphan*/  usbatm; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int CMD_MAX_CONFIG ; 
 int CMD_PACKET_SIZE ; 
 int /*<<< orphan*/  CM_REQUEST_CARD_DATA_SET ; 
 int EACCES ; 
 int EINVAL ; 
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  atm_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  atm_info (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int cxacru_cm (struct cxacru_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 
 int sscanf (char const*,char*,int*,int*,int*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  to_usb_interface (struct device*) ; 
 struct cxacru_data* to_usbatm_driver_data (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t adsl_config_store(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	struct cxacru_data *instance = to_usbatm_driver_data(
			to_usb_interface(dev));
	int len = strlen(buf);
	int ret, pos, num;
	__le32 data[CMD_PACKET_SIZE / 4];

	if (!capable(CAP_NET_ADMIN))
		return -EACCES;

	if (instance == NULL)
		return -ENODEV;

	pos = 0;
	num = 0;
	while (pos < len) {
		int tmp;
		u32 index;
		u32 value;

		ret = sscanf(buf + pos, "%x=%x%n", &index, &value, &tmp);
		if (ret < 2)
			return -EINVAL;
		if (index > 0x7f)
			return -EINVAL;
		if (tmp < 0 || tmp > len - pos)
			return -EINVAL;
		pos += tmp;

		/* skip trailing newline */
		if (buf[pos] == '\n' && pos == len-1)
			pos++;

		data[num * 2 + 1] = cpu_to_le32(index);
		data[num * 2 + 2] = cpu_to_le32(value);
		num++;

		/* send config values when data buffer is full
		 * or no more data
		 */
		if (pos >= len || num >= CMD_MAX_CONFIG) {
			char log[CMD_MAX_CONFIG * 12 + 1]; /* %02x=%08x */

			data[0] = cpu_to_le32(num);
			ret = cxacru_cm(instance, CM_REQUEST_CARD_DATA_SET,
				(u8 *) data, 4 + num * 8, NULL, 0);
			if (ret < 0) {
				atm_err(instance->usbatm,
					"set card data returned %d\n", ret);
				return -EIO;
			}

			for (tmp = 0; tmp < num; tmp++)
				snprintf(log + tmp*12, 13, " %02x=%08x",
					le32_to_cpu(data[tmp * 2 + 1]),
					le32_to_cpu(data[tmp * 2 + 2]));
			atm_info(instance->usbatm, "config%s\n", log);
			num = 0;
		}
	}

	return len;
}