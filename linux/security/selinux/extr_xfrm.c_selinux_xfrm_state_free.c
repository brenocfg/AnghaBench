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
struct xfrm_state {int /*<<< orphan*/  security; } ;

/* Variables and functions */
 int /*<<< orphan*/  selinux_xfrm_free (int /*<<< orphan*/ ) ; 

void selinux_xfrm_state_free(struct xfrm_state *x)
{
	selinux_xfrm_free(x->security);
}