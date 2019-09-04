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
struct TYPE_2__ {unsigned short sa_family; } ;
union sctp_addr {TYPE_1__ sa; } ;
struct sock {unsigned short sk_family; } ;
struct sctp_af {int (* is_any ) (union sctp_addr const*) ;} ;

/* Variables and functions */
 unsigned short AF_UNSPEC ; 
 struct sctp_af* sctp_get_af_specific (unsigned short) ; 
 int stub1 (union sctp_addr const*) ; 

int sctp_is_any(struct sock *sk, const union sctp_addr *addr)
{
	unsigned short fam = 0;
	struct sctp_af *af;

	/* Try to get the right address family */
	if (addr->sa.sa_family != AF_UNSPEC)
		fam = addr->sa.sa_family;
	else if (sk)
		fam = sk->sk_family;

	af = sctp_get_af_specific(fam);
	if (!af)
		return 0;

	return af->is_any(addr);
}