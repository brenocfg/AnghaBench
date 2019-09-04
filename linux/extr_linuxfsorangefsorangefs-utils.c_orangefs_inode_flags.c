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
struct ORANGEFS_sys_attr_s {int flags; } ;

/* Variables and functions */
 int ORANGEFS_APPEND_FL ; 
 int ORANGEFS_IMMUTABLE_FL ; 
 int ORANGEFS_NOATIME_FL ; 
 int S_APPEND ; 
 int S_IMMUTABLE ; 
 int S_NOATIME ; 

__attribute__((used)) static int orangefs_inode_flags(struct ORANGEFS_sys_attr_s *attrs)
{
	int flags = 0;
	if (attrs->flags & ORANGEFS_IMMUTABLE_FL)
		flags |= S_IMMUTABLE;
	else
		flags &= ~S_IMMUTABLE;
	if (attrs->flags & ORANGEFS_APPEND_FL)
		flags |= S_APPEND;
	else
		flags &= ~S_APPEND;
	if (attrs->flags & ORANGEFS_NOATIME_FL)
		flags |= S_NOATIME;
	else
		flags &= ~S_NOATIME;
	return flags;
}