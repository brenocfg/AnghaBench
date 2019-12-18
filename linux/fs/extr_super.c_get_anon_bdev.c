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
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int EMFILE ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int MINORBITS ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int ida_alloc_range (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unnamed_dev_ida ; 

int get_anon_bdev(dev_t *p)
{
	int dev;

	/*
	 * Many userspace utilities consider an FSID of 0 invalid.
	 * Always return at least 1 from get_anon_bdev.
	 */
	dev = ida_alloc_range(&unnamed_dev_ida, 1, (1 << MINORBITS) - 1,
			GFP_ATOMIC);
	if (dev == -ENOSPC)
		dev = -EMFILE;
	if (dev < 0)
		return dev;

	*p = MKDEV(0, dev);
	return 0;
}