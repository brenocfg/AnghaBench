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
struct ntb_transport_qp {int link_is_up; } ;

/* Variables and functions */

bool ntb_transport_link_query(struct ntb_transport_qp *qp)
{
	if (!qp)
		return false;

	return qp->link_is_up;
}