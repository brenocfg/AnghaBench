#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ vcn; scalar_t__ length; } ;
typedef  TYPE_1__ runlist_element ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  ntfs_rl_mc (TYPE_1__*,int,TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ntfs_rl_mm (TYPE_1__*,int,int,int) ; 
 TYPE_1__* ntfs_rl_realloc (TYPE_1__*,int,int) ; 

__attribute__((used)) static inline runlist_element *ntfs_rl_split(runlist_element *dst, int dsize,
		runlist_element *src, int ssize, int loc)
{
	BUG_ON(!dst);
	BUG_ON(!src);

	/* Space required: @dst size + @src size + one new hole. */
	dst = ntfs_rl_realloc(dst, dsize, dsize + ssize + 1);
	if (IS_ERR(dst))
		return dst;
	/*
	 * We are guaranteed to succeed from here so can start modifying the
	 * original runlists.
	 */

	/* Move the tail of @dst out of the way, then copy in @src. */
	ntfs_rl_mm(dst, loc + 1 + ssize, loc, dsize - loc);
	ntfs_rl_mc(dst, loc + 1, src, 0, ssize);

	/* Adjust the size of the holes either size of @src. */
	dst[loc].length		= dst[loc+1].vcn       - dst[loc].vcn;
	dst[loc+ssize+1].vcn    = dst[loc+ssize].vcn   + dst[loc+ssize].length;
	dst[loc+ssize+1].length = dst[loc+ssize+2].vcn - dst[loc+ssize+1].vcn;

	return dst;
}