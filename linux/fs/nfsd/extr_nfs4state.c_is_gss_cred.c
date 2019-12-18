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
struct svc_cred {scalar_t__ cr_flavor; } ;

/* Variables and functions */
 scalar_t__ RPC_AUTH_MAXFLAVOR ; 

__attribute__((used)) static bool is_gss_cred(struct svc_cred *cr)
{
	/* Is cr_flavor one of the gss "pseudoflavors"?: */
	return (cr->cr_flavor > RPC_AUTH_MAXFLAVOR);
}