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
struct lwtunnel_state {int dummy; } ;
struct TYPE_2__ {scalar_t__ v64; } ;
struct ila_params {TYPE_1__ locator; } ;

/* Variables and functions */
 struct ila_params* ila_params_lwtunnel (struct lwtunnel_state*) ; 

__attribute__((used)) static int ila_encap_cmp(struct lwtunnel_state *a, struct lwtunnel_state *b)
{
	struct ila_params *a_p = ila_params_lwtunnel(a);
	struct ila_params *b_p = ila_params_lwtunnel(b);

	return (a_p->locator.v64 != b_p->locator.v64);
}