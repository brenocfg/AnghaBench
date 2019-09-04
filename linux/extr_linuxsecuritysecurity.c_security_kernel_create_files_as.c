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
struct cred {int dummy; } ;

/* Variables and functions */
 int call_int_hook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cred*,struct inode*) ; 
 int /*<<< orphan*/  kernel_create_files_as ; 

int security_kernel_create_files_as(struct cred *new, struct inode *inode)
{
	return call_int_hook(kernel_create_files_as, 0, new, inode);
}