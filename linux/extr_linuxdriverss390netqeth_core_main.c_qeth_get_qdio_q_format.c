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
struct TYPE_2__ {scalar_t__ type; } ;
struct qeth_card {TYPE_1__ info; } ;

/* Variables and functions */
 int QDIO_IQDIO_QFMT ; 
 int QDIO_QETH_QFMT ; 
 scalar_t__ QETH_CARD_TYPE_IQD ; 

__attribute__((used)) static int qeth_get_qdio_q_format(struct qeth_card *card)
{
	if (card->info.type == QETH_CARD_TYPE_IQD)
		return QDIO_IQDIO_QFMT;
	else
		return QDIO_QETH_QFMT;
}