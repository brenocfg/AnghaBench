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
struct TYPE_2__ {int /*<<< orphan*/  func; } ;
struct mrp_application {TYPE_1__ pkttype; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_add_pack (TYPE_1__*) ; 
 int /*<<< orphan*/  mrp_rcv ; 

int mrp_register_application(struct mrp_application *appl)
{
	appl->pkttype.func = mrp_rcv;
	dev_add_pack(&appl->pkttype);
	return 0;
}