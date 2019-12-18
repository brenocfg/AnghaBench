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
struct fs_context {int /*<<< orphan*/  net_ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_net (int /*<<< orphan*/ ) ; 
 int get_tree_keyed (struct fs_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd_fill_super ; 

__attribute__((used)) static int nfsd_fs_get_tree(struct fs_context *fc)
{
	return get_tree_keyed(fc, nfsd_fill_super, get_net(fc->net_ns));
}