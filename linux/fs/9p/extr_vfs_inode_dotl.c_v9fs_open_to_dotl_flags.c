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

/* Variables and functions */
 int O_ACCMODE ; 
 int v9fs_mapped_dotl_flags (int) ; 

int v9fs_open_to_dotl_flags(int flags)
{
	int rflags = 0;

	/*
	 * We have same bits for P9_DOTL_READONLY, P9_DOTL_WRONLY
	 * and P9_DOTL_NOACCESS
	 */
	rflags |= flags & O_ACCMODE;
	rflags |= v9fs_mapped_dotl_flags(flags);

	return rflags;
}