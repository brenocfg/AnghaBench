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
struct nfs42_layouterror_data {int /*<<< orphan*/  inode; int /*<<< orphan*/  lseg; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nfs42_layouterror_data*) ; 
 int /*<<< orphan*/  nfs_iput_and_deactive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnfs_put_lseg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nfs42_free_layouterror_data(struct nfs42_layouterror_data *data)
{
	pnfs_put_lseg(data->lseg);
	nfs_iput_and_deactive(data->inode);
	kfree(data);
}