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
struct pnfs_layout_range {int offset; int length; scalar_t__ iomode; } ;
typedef  int s64 ;

/* Variables and functions */
 scalar_t__ IOMODE_READ ; 

__attribute__((used)) static s64
pnfs_lseg_range_cmp(const struct pnfs_layout_range *l1,
	   const struct pnfs_layout_range *l2)
{
	s64 d;

	/* high offset > low offset */
	d = l1->offset - l2->offset;
	if (d)
		return d;

	/* short length > long length */
	d = l2->length - l1->length;
	if (d)
		return d;

	/* read > read/write */
	return (int)(l1->iomode == IOMODE_READ) - (int)(l2->iomode == IOMODE_READ);
}