#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ sa_family; } ;
struct TYPE_4__ {int /*<<< orphan*/  sin6_addr; } ;
union sctp_addr {TYPE_3__ sa; TYPE_1__ v6; } ;
struct sockaddr {int dummy; } ;
struct sctp_sock {TYPE_2__* pf; } ;
struct sctp_af {int sockaddr_len; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* af_supported ) (scalar_t__,struct sctp_sock*) ;} ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int SIN6_LEN_RFC2133 ; 
 scalar_t__ ipv6_addr_v4mapped (int /*<<< orphan*/ *) ; 
 struct sctp_af* sctp_get_af_specific (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,struct sctp_sock*) ; 
 int /*<<< orphan*/  stub2 (scalar_t__,struct sctp_sock*) ; 

__attribute__((used)) static struct sctp_af *sctp_sockaddr_af(struct sctp_sock *opt,
					union sctp_addr *addr, int len)
{
	struct sctp_af *af;

	/* Check minimum size.  */
	if (len < sizeof (struct sockaddr))
		return NULL;

	if (!opt->pf->af_supported(addr->sa.sa_family, opt))
		return NULL;

	if (addr->sa.sa_family == AF_INET6) {
		if (len < SIN6_LEN_RFC2133)
			return NULL;
		/* V4 mapped address are really of AF_INET family */
		if (ipv6_addr_v4mapped(&addr->v6.sin6_addr) &&
		    !opt->pf->af_supported(AF_INET, opt))
			return NULL;
	}

	/* If we get this far, af is valid. */
	af = sctp_get_af_specific(addr->sa.sa_family);

	if (len < af->sockaddr_len)
		return NULL;

	return af;
}