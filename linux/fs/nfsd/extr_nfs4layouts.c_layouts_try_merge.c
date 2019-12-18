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
struct nfsd4_layout_seg {scalar_t__ iomode; scalar_t__ offset; } ;

/* Variables and functions */
 scalar_t__ layout_end (struct nfsd4_layout_seg*) ; 
 int /*<<< orphan*/  layout_update_len (struct nfsd4_layout_seg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max (scalar_t__,scalar_t__) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 

__attribute__((used)) static bool
layouts_try_merge(struct nfsd4_layout_seg *lo, struct nfsd4_layout_seg *new)
{
	if (lo->iomode != new->iomode)
		return false;
	if (layout_end(new) < lo->offset)
		return false;
	if (layout_end(lo) < new->offset)
		return false;

	lo->offset = min(lo->offset, new->offset);
	layout_update_len(lo, max(layout_end(lo), layout_end(new)));
	return true;
}