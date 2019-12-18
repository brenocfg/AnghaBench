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
typedef  scalar_t__ u32 ;
struct tcpnv {scalar_t__ nv_lower_bound_rtt; scalar_t__ nv_base_rtt; } ;

/* Variables and functions */

inline u32 nv_get_bounded_rtt(struct tcpnv *ca, u32 val)
{
	if (ca->nv_lower_bound_rtt > 0 && val < ca->nv_lower_bound_rtt)
		return ca->nv_lower_bound_rtt;
	else if (ca->nv_base_rtt > 0 && val > ca->nv_base_rtt)
		return ca->nv_base_rtt;
	else
		return val;
}