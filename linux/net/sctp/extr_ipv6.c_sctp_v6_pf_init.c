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

/* Variables and functions */
 int /*<<< orphan*/  PF_INET6 ; 
 int /*<<< orphan*/  sctp_af_inet6 ; 
 int /*<<< orphan*/  sctp_pf_inet6 ; 
 int /*<<< orphan*/  sctp_register_af (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_register_pf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void sctp_v6_pf_init(void)
{
	/* Register the SCTP specific PF_INET6 functions. */
	sctp_register_pf(&sctp_pf_inet6, PF_INET6);

	/* Register the SCTP specific AF_INET6 functions. */
	sctp_register_af(&sctp_af_inet6);
}