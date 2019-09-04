#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device_attribute {int /*<<< orphan*/  attr; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_4__ {int status; int /*<<< orphan*/  handle; TYPE_1__* attrs; } ;
struct TYPE_3__ {int /*<<< orphan*/  attr; } ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t EIO ; 
 unsigned int LID_RESUME_MAX ; 
 unsigned int LID_RESUME_S5 ; 
 scalar_t__ kstrtoul (char const*,int,unsigned long*) ; 
 TYPE_2__* lid_ctl ; 
 scalar_t__ sony_call_snc_handle (int /*<<< orphan*/ ,unsigned long,unsigned int*) ; 

__attribute__((used)) static ssize_t sony_nc_lid_resume_store(struct device *dev,
					struct device_attribute *attr,
					const char *buffer, size_t count)
{
	unsigned int result;
	unsigned long value;
	unsigned int pos = LID_RESUME_S5;
	if (count > 31)
		return -EINVAL;

	if (kstrtoul(buffer, 10, &value) || value > 1)
		return -EINVAL;

	/* the value we have to write to SNC is a bitmask:
	 * +--------------+
	 * | S3 | S4 | S5 |
	 * +--------------+
	 *   2    1    0
	 */
	while (pos < LID_RESUME_MAX) {
		if (&lid_ctl->attrs[pos].attr == &attr->attr)
			break;
		pos++;
	}
	if (pos == LID_RESUME_MAX)
		return -EINVAL;

	if (value)
		value = lid_ctl->status | (1 << pos);
	else
		value = lid_ctl->status & ~(1 << pos);

	if (sony_call_snc_handle(lid_ctl->handle, value << 0x10 | 0x0100,
				&result))
		return -EIO;

	lid_ctl->status = value;

	return count;
}