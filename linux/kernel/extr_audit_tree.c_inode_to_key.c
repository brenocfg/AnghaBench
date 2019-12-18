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
struct inode {int /*<<< orphan*/  i_fsnotify_marks; } ;

/* Variables and functions */

__attribute__((used)) static unsigned long inode_to_key(const struct inode *inode)
{
	/* Use address pointed to by connector->obj as the key */
	return (unsigned long)&inode->i_fsnotify_marks;
}