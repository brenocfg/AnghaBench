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
struct xt_tcp {int invflags; } ;
struct xt_mtchk_param {struct xt_tcp* matchinfo; } ;

/* Variables and functions */
 int EINVAL ; 
 int XT_TCP_INV_MASK ; 

__attribute__((used)) static int tcp_mt_check(const struct xt_mtchk_param *par)
{
	const struct xt_tcp *tcpinfo = par->matchinfo;

	/* Must specify no unknown invflags */
	return (tcpinfo->invflags & ~XT_TCP_INV_MASK) ? -EINVAL : 0;
}