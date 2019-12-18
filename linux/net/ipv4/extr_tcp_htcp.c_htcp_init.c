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
struct sock {int dummy; } ;
struct htcp {int pkts_acked; int /*<<< orphan*/  last_cong; int /*<<< orphan*/  beta; int /*<<< orphan*/  alpha; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALPHA_BASE ; 
 int /*<<< orphan*/  BETA_MIN ; 
 struct htcp* inet_csk_ca (struct sock*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  memset (struct htcp*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void htcp_init(struct sock *sk)
{
	struct htcp *ca = inet_csk_ca(sk);

	memset(ca, 0, sizeof(struct htcp));
	ca->alpha = ALPHA_BASE;
	ca->beta = BETA_MIN;
	ca->pkts_acked = 1;
	ca->last_cong = jiffies;
}