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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct mt7601u_dev {int /*<<< orphan*/  vendor_req_mutex; } ;

/* Variables and functions */
 int __mt7601u_vendor_single_wr (struct mt7601u_dev*,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int mt7601u_vendor_single_wr(struct mt7601u_dev *dev, const u8 req,
			     const u16 offset, const u32 val)
{
	int ret;

	mutex_lock(&dev->vendor_req_mutex);
	ret = __mt7601u_vendor_single_wr(dev, req, offset, val);
	mutex_unlock(&dev->vendor_req_mutex);

	return ret;
}