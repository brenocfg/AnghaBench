#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nfsd_net {int dummy; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_4__ {TYPE_1__* i_sb; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_fs_info; } ;

/* Variables and functions */
 TYPE_2__* file_inode (struct file*) ; 
 struct nfsd_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd_net_id ; 
 int /*<<< orphan*/  nfsd_reply_cache_stats_show ; 
 int single_open (struct file*,int /*<<< orphan*/ ,struct nfsd_net*) ; 

int nfsd_reply_cache_stats_open(struct inode *inode, struct file *file)
{
	struct nfsd_net *nn = net_generic(file_inode(file)->i_sb->s_fs_info,
								nfsd_net_id);

	return single_open(file, nfsd_reply_cache_stats_show, nn);
}