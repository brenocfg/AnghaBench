#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct vme_master_resource {int number; int /*<<< orphan*/  lock; struct vme_bridge* parent; } ;
struct vme_bridge {struct fake_driver* driver_priv; } ;
struct fake_driver {TYPE_1__* masters; } ;
typedef  int ssize_t ;
typedef  unsigned long long loff_t ;
struct TYPE_2__ {unsigned long long vme_base; scalar_t__ aspace; scalar_t__ cycle; scalar_t__ dwidth; } ;

/* Variables and functions */
 scalar_t__ VME_D16 ; 
 scalar_t__ VME_D32 ; 
 scalar_t__ VME_D8 ; 
 int /*<<< orphan*/  fake_vmewrite16 (struct fake_driver*,int /*<<< orphan*/ *,unsigned long long,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  fake_vmewrite32 (struct fake_driver*,scalar_t__*,unsigned long long,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  fake_vmewrite8 (struct fake_driver*,int /*<<< orphan*/ *,unsigned long long,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t fake_master_write(struct vme_master_resource *image, void *buf,
		size_t count, loff_t offset)
{
	int retval = 0;
	u32 aspace, cycle, dwidth;
	unsigned long long addr;
	int i;
	unsigned int done = 0;
	unsigned int count32;

	struct vme_bridge *fake_bridge;
	struct fake_driver *bridge;

	fake_bridge = image->parent;

	bridge = fake_bridge->driver_priv;

	i = image->number;

	addr = bridge->masters[i].vme_base + offset;
	aspace = bridge->masters[i].aspace;
	cycle = bridge->masters[i].cycle;
	dwidth = bridge->masters[i].dwidth;

	spin_lock(&image->lock);

	/* Here we apply for the same strategy we do in master_read
	 * function in order to assure the correct cycles.
	 */
	if (addr & 0x1) {
		fake_vmewrite8(bridge, (u8 *)buf, addr, aspace, cycle);
		done += 1;
		if (done == count)
			goto out;
	}

	if ((dwidth == VME_D16) || (dwidth == VME_D32)) {
		if ((addr + done) & 0x2) {
			if ((count - done) < 2) {
				fake_vmewrite8(bridge, (u8 *)(buf + done),
						addr + done, aspace, cycle);
				done += 1;
				goto out;
			} else {
				fake_vmewrite16(bridge, (u16 *)(buf + done),
						addr + done, aspace, cycle);
				done += 2;
			}
		}
	}

	if (dwidth == VME_D32) {
		count32 = (count - done) & ~0x3;
		while (done < count32) {
			fake_vmewrite32(bridge, (u32 *)(buf + done),
					addr + done, aspace, cycle);
			done += 4;
		}
	} else if (dwidth == VME_D16) {
		count32 = (count - done) & ~0x3;
		while (done < count32) {
			fake_vmewrite16(bridge, (u16 *)(buf + done),
					addr + done, aspace, cycle);
			done += 2;
		}
	} else if (dwidth == VME_D8) {
		count32 = (count - done);
		while (done < count32) {
			fake_vmewrite8(bridge, (u8 *)(buf + done), addr + done,
					aspace, cycle);
			done += 1;
		}

	}

	if ((dwidth == VME_D16) || (dwidth == VME_D32)) {
		if ((count - done) & 0x2) {
			fake_vmewrite16(bridge, (u16 *)(buf + done),
					addr + done, aspace, cycle);
			done += 2;
		}
	}

	if ((count - done) & 0x1) {
		fake_vmewrite8(bridge, (u8 *)(buf + done), addr + done, aspace,
				cycle);
		done += 1;
	}

out:
	retval = count;

	spin_unlock(&image->lock);

	return retval;
}