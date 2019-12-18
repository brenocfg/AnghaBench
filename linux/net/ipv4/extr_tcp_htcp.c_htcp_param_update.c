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
struct sock {int dummy; } ;
struct htcp {scalar_t__ minRTT; scalar_t__ maxRTT; } ;

/* Variables and functions */
 int /*<<< orphan*/  htcp_alpha_update (struct htcp*) ; 
 int /*<<< orphan*/  htcp_beta_update (struct htcp*,scalar_t__,scalar_t__) ; 
 struct htcp* inet_csk_ca (struct sock*) ; 

__attribute__((used)) static void htcp_param_update(struct sock *sk)
{
	struct htcp *ca = inet_csk_ca(sk);
	u32 minRTT = ca->minRTT;
	u32 maxRTT = ca->maxRTT;

	htcp_beta_update(ca, minRTT, maxRTT);
	htcp_alpha_update(ca);

	/* add slowly fading memory for maxRTT to accommodate routing changes */
	if (minRTT > 0 && maxRTT > minRTT)
		ca->maxRTT = minRTT + ((maxRTT - minRTT) * 95) / 100;
}