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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct rio_dev {int dummy; } ;
struct kobject {int dummy; } ;
struct file {int dummy; } ;
struct bin_attribute {int dummy; } ;
typedef  size_t ssize_t ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 scalar_t__ RIO_MAINT_SPACE_SZ ; 
 int /*<<< orphan*/  kobj_to_dev (struct kobject*) ; 
 int /*<<< orphan*/  rio_write_config_16 (struct rio_dev*,scalar_t__,int) ; 
 int /*<<< orphan*/  rio_write_config_32 (struct rio_dev*,scalar_t__,int) ; 
 int /*<<< orphan*/  rio_write_config_8 (struct rio_dev*,scalar_t__,int) ; 
 struct rio_dev* to_rio_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
rio_write_config(struct file *filp, struct kobject *kobj,
		 struct bin_attribute *bin_attr,
		 char *buf, loff_t off, size_t count)
{
	struct rio_dev *dev = to_rio_dev(kobj_to_dev(kobj));
	unsigned int size = count;
	loff_t init_off = off;
	u8 *data = (u8 *) buf;

	if (off >= RIO_MAINT_SPACE_SZ)
		return 0;
	if (off + count > RIO_MAINT_SPACE_SZ) {
		size = RIO_MAINT_SPACE_SZ - off;
		count = size;
	}

	if ((off & 1) && size) {
		rio_write_config_8(dev, off, data[off - init_off]);
		off++;
		size--;
	}

	if ((off & 3) && (size > 2)) {
		u16 val = data[off - init_off + 1];
		val |= (u16) data[off - init_off] << 8;
		rio_write_config_16(dev, off, val);
		off += 2;
		size -= 2;
	}

	while (size > 3) {
		u32 val = data[off - init_off + 3];
		val |= (u32) data[off - init_off + 2] << 8;
		val |= (u32) data[off - init_off + 1] << 16;
		val |= (u32) data[off - init_off] << 24;
		rio_write_config_32(dev, off, val);
		off += 4;
		size -= 4;
	}

	if (size >= 2) {
		u16 val = data[off - init_off + 1];
		val |= (u16) data[off - init_off] << 8;
		rio_write_config_16(dev, off, val);
		off += 2;
		size -= 2;
	}

	if (size) {
		rio_write_config_8(dev, off, data[off - init_off]);
		off++;
		--size;
	}

	return count;
}