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
 int SB_MANDLOCK ; 
 int SB_RDONLY ; 
 int SB_SYNCHRONOUS ; 
 int ST_MANDLOCK ; 
 int ST_RDONLY ; 
 int ST_SYNCHRONOUS ; 

__attribute__((used)) static int flags_by_sb(int s_flags)
{
	int flags = 0;
	if (s_flags & SB_SYNCHRONOUS)
		flags |= ST_SYNCHRONOUS;
	if (s_flags & SB_MANDLOCK)
		flags |= ST_MANDLOCK;
	if (s_flags & SB_RDONLY)
		flags |= ST_RDONLY;
	return flags;
}