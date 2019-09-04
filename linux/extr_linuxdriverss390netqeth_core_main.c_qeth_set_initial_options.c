#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* type; } ;
struct TYPE_4__ {void* type; } ;
struct TYPE_6__ {int /*<<< orphan*/  cq; int /*<<< orphan*/  isolation; int /*<<< orphan*/  rx_sg_cb; TYPE_2__ route6; TYPE_1__ route4; } ;
struct qeth_card {TYPE_3__ options; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISOLATION_MODE_NONE ; 
 void* NO_ROUTER ; 
 int /*<<< orphan*/  QETH_CQ_DISABLED ; 
 int /*<<< orphan*/  QETH_RX_SG_CB ; 

__attribute__((used)) static void qeth_set_initial_options(struct qeth_card *card)
{
	card->options.route4.type = NO_ROUTER;
	card->options.route6.type = NO_ROUTER;
	card->options.rx_sg_cb = QETH_RX_SG_CB;
	card->options.isolation = ISOLATION_MODE_NONE;
	card->options.cq = QETH_CQ_DISABLED;
}