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
 int AT_REMOVEDIR ; 
 int P9_DOTL_AT_REMOVEDIR ; 

__attribute__((used)) static int v9fs_at_to_dotl_flags(int flags)
{
	int rflags = 0;
	if (flags & AT_REMOVEDIR)
		rflags |= P9_DOTL_AT_REMOVEDIR;
	return rflags;
}