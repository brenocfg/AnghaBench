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
struct qeth_card {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ CARD_STATE_SOFTSETUP ; 
 scalar_t__ CARD_STATE_UP ; 

int qeth_card_hw_is_reachable(struct qeth_card *card)
{
	return (card->state == CARD_STATE_SOFTSETUP) ||
		(card->state == CARD_STATE_UP);
}