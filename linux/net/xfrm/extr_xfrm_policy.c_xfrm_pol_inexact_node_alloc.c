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
typedef  int /*<<< orphan*/  xfrm_address_t ;
typedef  int /*<<< orphan*/  u8 ;
struct xfrm_pol_inexact_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct xfrm_pol_inexact_node* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_pol_inexact_node_init (struct xfrm_pol_inexact_node*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct xfrm_pol_inexact_node *
xfrm_pol_inexact_node_alloc(const xfrm_address_t *addr, u8 prefixlen)
{
	struct xfrm_pol_inexact_node *node;

	node = kzalloc(sizeof(*node), GFP_ATOMIC);
	if (node)
		xfrm_pol_inexact_node_init(node, addr, prefixlen);

	return node;
}