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
struct tb_xdomain {int dummy; } ;
struct tb {TYPE_1__* cm_ops; } ;
struct TYPE_2__ {int (* approve_xdomain_paths ) (struct tb*,struct tb_xdomain*) ;} ;

/* Variables and functions */
 int ENOTSUPP ; 
 int stub1 (struct tb*,struct tb_xdomain*) ; 

int tb_domain_approve_xdomain_paths(struct tb *tb, struct tb_xdomain *xd)
{
	if (!tb->cm_ops->approve_xdomain_paths)
		return -ENOTSUPP;

	return tb->cm_ops->approve_xdomain_paths(tb, xd);
}