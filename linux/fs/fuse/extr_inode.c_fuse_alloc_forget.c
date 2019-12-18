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
struct fuse_forget_link {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL_ACCOUNT ; 
 struct fuse_forget_link* kzalloc (int,int /*<<< orphan*/ ) ; 

struct fuse_forget_link *fuse_alloc_forget(void)
{
	return kzalloc(sizeof(struct fuse_forget_link), GFP_KERNEL_ACCOUNT);
}