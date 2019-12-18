#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ lcn; scalar_t__ length; scalar_t__ vcn; } ;
typedef  TYPE_1__ runlist_element ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 scalar_t__ LCN_ENOENT ; 
 int /*<<< orphan*/  __ntfs_rl_merge (TYPE_1__*,TYPE_1__*) ; 
 int ntfs_are_rl_mergeable (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  ntfs_rl_mc (TYPE_1__*,int,TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ntfs_rl_mm (TYPE_1__*,int,int,int) ; 
 TYPE_1__* ntfs_rl_realloc (TYPE_1__*,int,int) ; 

__attribute__((used)) static inline runlist_element *ntfs_rl_append(runlist_element *dst,
		int dsize, runlist_element *src, int ssize, int loc)
{
	bool right = false;	/* Right end of @src needs merging. */
	int marker;		/* End of the inserted runs. */

	BUG_ON(!dst);
	BUG_ON(!src);

	/* First, check if the right hand end needs merging. */
	if ((loc + 1) < dsize)
		right = ntfs_are_rl_mergeable(src + ssize - 1, dst + loc + 1);

	/* Space required: @dst size + @src size, less one if we merged. */
	dst = ntfs_rl_realloc(dst, dsize, dsize + ssize - right);
	if (IS_ERR(dst))
		return dst;
	/*
	 * We are guaranteed to succeed from here so can start modifying the
	 * original runlists.
	 */

	/* First, merge the right hand end, if necessary. */
	if (right)
		__ntfs_rl_merge(src + ssize - 1, dst + loc + 1);

	/* First run after the @src runs that have been inserted. */
	marker = loc + ssize + 1;

	/* Move the tail of @dst out of the way, then copy in @src. */
	ntfs_rl_mm(dst, marker, loc + 1 + right, dsize - (loc + 1 + right));
	ntfs_rl_mc(dst, loc + 1, src, 0, ssize);

	/* Adjust the size of the preceding hole. */
	dst[loc].length = dst[loc + 1].vcn - dst[loc].vcn;

	/* We may have changed the length of the file, so fix the end marker */
	if (dst[marker].lcn == LCN_ENOENT)
		dst[marker].vcn = dst[marker - 1].vcn + dst[marker - 1].length;

	return dst;
}