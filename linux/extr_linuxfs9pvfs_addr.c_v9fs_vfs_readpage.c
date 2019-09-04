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
struct page {int dummy; } ;
struct file {int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
 int v9fs_fid_readpage (int /*<<< orphan*/ ,struct page*) ; 

__attribute__((used)) static int v9fs_vfs_readpage(struct file *filp, struct page *page)
{
	return v9fs_fid_readpage(filp->private_data, page);
}