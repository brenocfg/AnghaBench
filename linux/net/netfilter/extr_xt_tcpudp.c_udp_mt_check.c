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
struct xt_udp {int invflags; } ;
struct xt_mtchk_param {struct xt_udp* matchinfo; } ;

/* Variables and functions */
 int EINVAL ; 
 int XT_UDP_INV_MASK ; 

__attribute__((used)) static int udp_mt_check(const struct xt_mtchk_param *par)
{
	const struct xt_udp *udpinfo = par->matchinfo;

	/* Must specify no unknown invflags */
	return (udpinfo->invflags & ~XT_UDP_INV_MASK) ? -EINVAL : 0;
}