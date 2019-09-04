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
struct inode {int dummy; } ;
struct dir_context {scalar_t__ pos; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_CAP_READDIRPLUS ; 
 TYPE_1__* NFS_I (struct inode*) ; 
 int /*<<< orphan*/  NFS_INO_ADVISE_RDPLUS ; 
 int /*<<< orphan*/  nfs_server_capable (struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
bool nfs_use_readdirplus(struct inode *dir, struct dir_context *ctx)
{
	if (!nfs_server_capable(dir, NFS_CAP_READDIRPLUS))
		return false;
	if (test_and_clear_bit(NFS_INO_ADVISE_RDPLUS, &NFS_I(dir)->flags))
		return true;
	if (ctx->pos == 0)
		return true;
	return false;
}