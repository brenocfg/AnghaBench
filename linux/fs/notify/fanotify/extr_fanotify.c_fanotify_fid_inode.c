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
typedef  int u32 ;
struct path {int /*<<< orphan*/  dentry; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int ALL_FSNOTIFY_DIRENT_EVENTS ; 
 int FSNOTIFY_EVENT_INODE ; 
 int FSNOTIFY_EVENT_PATH ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct inode *fanotify_fid_inode(struct inode *to_tell, u32 event_mask,
					const void *data, int data_type)
{
	if (event_mask & ALL_FSNOTIFY_DIRENT_EVENTS)
		return to_tell;
	else if (data_type == FSNOTIFY_EVENT_INODE)
		return (struct inode *)data;
	else if (data_type == FSNOTIFY_EVENT_PATH)
		return d_inode(((struct path *)data)->dentry);
	return NULL;
}