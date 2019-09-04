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
struct device_driver {int dummy; } ;
struct bus_id_priv {int /*<<< orphan*/  status; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int BUSID_SIZE ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  STUB_BUSID_OTHER ; 
 int /*<<< orphan*/  del_match_busid (char*) ; 
 int do_rebind (char*,struct bus_id_priv*) ; 
 struct bus_id_priv* get_busid_priv (char const*) ; 
 int /*<<< orphan*/  put_busid_priv (struct bus_id_priv*) ; 
 int strnlen (char const*,int) ; 

__attribute__((used)) static ssize_t rebind_store(struct device_driver *dev, const char *buf,
				 size_t count)
{
	int ret;
	int len;
	struct bus_id_priv *bid;

	/* buf length should be less that BUSID_SIZE */
	len = strnlen(buf, BUSID_SIZE);

	if (!(len < BUSID_SIZE))
		return -EINVAL;

	bid = get_busid_priv(buf);
	if (!bid)
		return -ENODEV;

	/* mark the device for deletion so probe ignores it during rescan */
	bid->status = STUB_BUSID_OTHER;
	/* release the busid lock */
	put_busid_priv(bid);

	ret = do_rebind((char *) buf, bid);
	if (ret < 0)
		return ret;

	/* delete device from busid_table */
	del_match_busid((char *) buf);

	return count;
}