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
typedef  int /*<<< orphan*/  uuid ;
typedef  int u8 ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,int,char const,int,char const) ; 
 int hex_to_bin (char const) ; 
 scalar_t__ is_uuid_sep (char const) ; 
 int /*<<< orphan*/  isxdigit (char const) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

__attribute__((used)) static int nd_uuid_parse(struct device *dev, u8 *uuid_out, const char *buf,
		size_t len)
{
	const char *str = buf;
	u8 uuid[16];
	int i;

	for (i = 0; i < 16; i++) {
		if (!isxdigit(str[0]) || !isxdigit(str[1])) {
			dev_dbg(dev, "pos: %d buf[%zd]: %c buf[%zd]: %c\n",
					i, str - buf, str[0],
					str + 1 - buf, str[1]);
			return -EINVAL;
		}

		uuid[i] = (hex_to_bin(str[0]) << 4) | hex_to_bin(str[1]);
		str += 2;
		if (is_uuid_sep(*str))
			str++;
	}

	memcpy(uuid_out, uuid, sizeof(uuid));
	return 0;
}