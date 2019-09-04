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
struct sctp_pf {int dummy; } ;
typedef  int sa_family_t ;

/* Variables and functions */
#define  PF_INET 129 
#define  PF_INET6 128 
 struct sctp_pf* sctp_pf_inet6_specific ; 
 struct sctp_pf* sctp_pf_inet_specific ; 

int sctp_register_pf(struct sctp_pf *pf, sa_family_t family)
{
	switch (family) {
	case PF_INET:
		if (sctp_pf_inet_specific)
			return 0;
		sctp_pf_inet_specific = pf;
		break;
	case PF_INET6:
		if (sctp_pf_inet6_specific)
			return 0;
		sctp_pf_inet6_specific = pf;
		break;
	default:
		return 0;
	}
	return 1;
}