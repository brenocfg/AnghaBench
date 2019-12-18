#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  union sctp_addr {int dummy; } sctp_addr ;
struct sock {int dummy; } ;
struct sctp_af {int /*<<< orphan*/  (* addr_valid ) (union sctp_addr*,TYPE_2__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_7__ {TYPE_1__* pf; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* send_verify ) (TYPE_2__*,union sctp_addr*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_2__* sctp_sk (struct sock*) ; 
 struct sctp_af* sctp_sockaddr_af (TYPE_2__*,union sctp_addr*,int) ; 
 int /*<<< orphan*/  stub1 (union sctp_addr*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,union sctp_addr*) ; 

__attribute__((used)) static inline int sctp_verify_addr(struct sock *sk, union sctp_addr *addr,
				   int len)
{
	struct sctp_af *af;

	/* Verify basic sockaddr. */
	af = sctp_sockaddr_af(sctp_sk(sk), addr, len);
	if (!af)
		return -EINVAL;

	/* Is this a valid SCTP address?  */
	if (!af->addr_valid(addr, sctp_sk(sk), NULL))
		return -EINVAL;

	if (!sctp_sk(sk)->pf->send_verify(sctp_sk(sk), (addr)))
		return -EINVAL;

	return 0;
}