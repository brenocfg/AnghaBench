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
struct nfs_io_completion {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct nfs_io_completion* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nfs_io_completion *nfs_io_completion_alloc(gfp_t gfp_flags)
{
	return kmalloc(sizeof(struct nfs_io_completion), gfp_flags);
}