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
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  sctp_af_inet ; 
 int /*<<< orphan*/  sctp_pf_inet ; 
 int /*<<< orphan*/  sctp_register_af (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_register_pf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sctp_v4_pf_init(void)
{
	/* Initialize the SCTP specific PF functions. */
	sctp_register_pf(&sctp_pf_inet, PF_INET);
	sctp_register_af(&sctp_af_inet);
}