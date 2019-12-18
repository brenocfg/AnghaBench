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
struct super_block {struct net* s_fs_info; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kill_litter_super (struct super_block*) ; 
 int /*<<< orphan*/  put_net (struct net*) ; 

__attribute__((used)) static void nfsd_umount(struct super_block *sb)
{
	struct net *net = sb->s_fs_info;

	kill_litter_super(sb);
	put_net(net);
}