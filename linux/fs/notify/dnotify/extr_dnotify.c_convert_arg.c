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
typedef  int __u32 ;

/* Variables and functions */
 unsigned long DN_ACCESS ; 
 unsigned long DN_ATTRIB ; 
 unsigned long DN_CREATE ; 
 unsigned long DN_DELETE ; 
 unsigned long DN_MODIFY ; 
 unsigned long DN_MULTISHOT ; 
 unsigned long DN_RENAME ; 
 int FS_ACCESS ; 
 int FS_ATTRIB ; 
 int FS_CREATE ; 
 int FS_DELETE ; 
 int FS_DN_MULTISHOT ; 
 int FS_DN_RENAME ; 
 int FS_EVENT_ON_CHILD ; 
 int FS_MODIFY ; 
 int FS_MOVED_FROM ; 
 int FS_MOVED_TO ; 

__attribute__((used)) static __u32 convert_arg(unsigned long arg)
{
	__u32 new_mask = FS_EVENT_ON_CHILD;

	if (arg & DN_MULTISHOT)
		new_mask |= FS_DN_MULTISHOT;
	if (arg & DN_DELETE)
		new_mask |= (FS_DELETE | FS_MOVED_FROM);
	if (arg & DN_MODIFY)
		new_mask |= FS_MODIFY;
	if (arg & DN_ACCESS)
		new_mask |= FS_ACCESS;
	if (arg & DN_ATTRIB)
		new_mask |= FS_ATTRIB;
	if (arg & DN_RENAME)
		new_mask |= FS_DN_RENAME;
	if (arg & DN_CREATE)
		new_mask |= (FS_CREATE | FS_MOVED_TO);

	return new_mask;
}