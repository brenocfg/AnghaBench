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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int layer2; } ;
struct qeth_card {TYPE_1__ options; } ;

/* Variables and functions */
 scalar_t__ IS_OSN (struct qeth_card*) ; 
 int /*<<< orphan*/  QETH_PROT_LAYER2 ; 
 int /*<<< orphan*/  QETH_PROT_OSN2 ; 
 int /*<<< orphan*/  QETH_PROT_TCPIP ; 

__attribute__((used)) static u8 qeth_mpc_select_prot_type(struct qeth_card *card)
{
	if (IS_OSN(card))
		return QETH_PROT_OSN2;
	return (card->options.layer2 == 1) ? QETH_PROT_LAYER2 : QETH_PROT_TCPIP;
}