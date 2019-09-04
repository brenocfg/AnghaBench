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
typedef  enum orangefs_ds_type { ____Placeholder_orangefs_ds_type } orangefs_ds_type ;

/* Variables and functions */
 int ORANGEFS_TYPE_DIRECTORY ; 
 int ORANGEFS_TYPE_METAFILE ; 
 int ORANGEFS_TYPE_SYMLINK ; 
 int S_IFDIR ; 
 int S_IFLNK ; 
 int S_IFREG ; 

__attribute__((used)) static int orangefs_inode_type(enum orangefs_ds_type objtype)
{
	if (objtype == ORANGEFS_TYPE_METAFILE)
		return S_IFREG;
	else if (objtype == ORANGEFS_TYPE_DIRECTORY)
		return S_IFDIR;
	else if (objtype == ORANGEFS_TYPE_SYMLINK)
		return S_IFLNK;
	else
		return -1;
}