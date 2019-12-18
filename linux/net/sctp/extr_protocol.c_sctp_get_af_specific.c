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
struct sctp_af {int dummy; } ;
typedef  int sa_family_t ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 struct sctp_af* sctp_af_v4_specific ; 
 struct sctp_af* sctp_af_v6_specific ; 

struct sctp_af *sctp_get_af_specific(sa_family_t family)
{
	switch (family) {
	case AF_INET:
		return sctp_af_v4_specific;
	case AF_INET6:
		return sctp_af_v6_specific;
	default:
		return NULL;
	}
}