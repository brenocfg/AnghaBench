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
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_void_hook (int /*<<< orphan*/ ,struct inode*) ; 
 int /*<<< orphan*/  inode_free_security ; 
 int /*<<< orphan*/  integrity_inode_free (struct inode*) ; 

void security_inode_free(struct inode *inode)
{
	integrity_inode_free(inode);
	call_void_hook(inode_free_security, inode);
}