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
typedef  int u32 ;
struct mt7601u_dev {int /*<<< orphan*/  vendor_req_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_VEND_WRITE ; 
 int __mt7601u_rr (struct mt7601u_dev*,int) ; 
 int /*<<< orphan*/  __mt7601u_vendor_single_wr (struct mt7601u_dev*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

u32 mt7601u_rmc(struct mt7601u_dev *dev, u32 offset, u32 mask, u32 val)
{
	u32 reg;

	mutex_lock(&dev->vendor_req_mutex);
	reg = __mt7601u_rr(dev, offset);
	val |= reg & ~mask;
	if (reg != val)
		__mt7601u_vendor_single_wr(dev, MT_VEND_WRITE,
					   offset, val);
	mutex_unlock(&dev->vendor_req_mutex);

	return val;
}