#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct swap_info_struct {int /*<<< orphan*/  pages; } ;
struct rpc_clnt {int dummy; } ;
struct file {TYPE_1__* f_mapping; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 struct rpc_clnt* NFS_CLIENT (int /*<<< orphan*/ ) ; 
 int rpc_clnt_swap_activate (struct rpc_clnt*) ; 

__attribute__((used)) static int nfs_swap_activate(struct swap_info_struct *sis, struct file *file,
						sector_t *span)
{
	struct rpc_clnt *clnt = NFS_CLIENT(file->f_mapping->host);

	*span = sis->pages;

	return rpc_clnt_swap_activate(clnt);
}