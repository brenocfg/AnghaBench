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
struct xfrm_if_parms {scalar_t__ link; int /*<<< orphan*/  if_id; } ;
struct TYPE_2__ {scalar_t__ link; int /*<<< orphan*/  if_id; } ;
struct xfrm_if {TYPE_1__ p; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int xfrmi_change(struct xfrm_if *xi, const struct xfrm_if_parms *p)
{
	if (xi->p.link != p->link)
		return -EINVAL;

	xi->p.if_id = p->if_id;

	return 0;
}