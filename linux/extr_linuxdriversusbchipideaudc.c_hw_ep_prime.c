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
struct ci_hdrc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int EAGAIN ; 
 int /*<<< orphan*/  OP_ENDPTPRIME ; 
 int /*<<< orphan*/  OP_ENDPTSETUPSTAT ; 
 int RX ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int hw_ep_bit (int,int) ; 
 scalar_t__ hw_read (struct ci_hdrc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_write (struct ci_hdrc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int hw_ep_prime(struct ci_hdrc *ci, int num, int dir, int is_ctrl)
{
	int n = hw_ep_bit(num, dir);

	/* Synchronize before ep prime */
	wmb();

	if (is_ctrl && dir == RX && hw_read(ci, OP_ENDPTSETUPSTAT, BIT(num)))
		return -EAGAIN;

	hw_write(ci, OP_ENDPTPRIME, ~0, BIT(n));

	while (hw_read(ci, OP_ENDPTPRIME, BIT(n)))
		cpu_relax();
	if (is_ctrl && dir == RX && hw_read(ci, OP_ENDPTSETUPSTAT, BIT(num)))
		return -EAGAIN;

	/* status shoult be tested according with manual but it doesn't work */
	return 0;
}