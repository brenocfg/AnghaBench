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
struct TYPE_2__ {int /*<<< orphan*/  ctl_sock; } ;
struct net {TYPE_1__ sctp; } ;
typedef  scalar_t__ sa_family_t ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  IPPROTO_SCTP ; 
 scalar_t__ PF_INET ; 
 scalar_t__ PF_INET6 ; 
 int /*<<< orphan*/  SOCK_SEQPACKET ; 
 int inet_ctl_sock_create (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ sctp_get_pf_specific (scalar_t__) ; 

__attribute__((used)) static int sctp_ctl_sock_init(struct net *net)
{
	int err;
	sa_family_t family = PF_INET;

	if (sctp_get_pf_specific(PF_INET6))
		family = PF_INET6;

	err = inet_ctl_sock_create(&net->sctp.ctl_sock, family,
				   SOCK_SEQPACKET, IPPROTO_SCTP, net);

	/* If IPv6 socket could not be created, try the IPv4 socket */
	if (err < 0 && family == PF_INET6)
		err = inet_ctl_sock_create(&net->sctp.ctl_sock, AF_INET,
					   SOCK_SEQPACKET, IPPROTO_SCTP,
					   net);

	if (err < 0) {
		pr_err("Failed to create the SCTP control socket\n");
		return err;
	}
	return 0;
}