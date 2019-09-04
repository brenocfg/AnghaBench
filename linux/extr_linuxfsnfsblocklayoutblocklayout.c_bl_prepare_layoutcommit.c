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
struct nfs4_layoutcommit_args {int dummy; } ;

/* Variables and functions */
 int ext_tree_prepare_commit (struct nfs4_layoutcommit_args*) ; 

__attribute__((used)) static int
bl_prepare_layoutcommit(struct nfs4_layoutcommit_args *arg)
{
	return ext_tree_prepare_commit(arg);
}