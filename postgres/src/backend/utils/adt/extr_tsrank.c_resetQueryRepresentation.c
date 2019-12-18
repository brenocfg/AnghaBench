#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* operandData; TYPE_1__* query; } ;
struct TYPE_6__ {int operandexists; int reverseinsert; scalar_t__ npos; } ;
struct TYPE_5__ {int size; } ;
typedef  TYPE_3__ QueryRepresentation ;

/* Variables and functions */

__attribute__((used)) static void
resetQueryRepresentation(QueryRepresentation *qr, bool reverseinsert)
{
	int			i;

	for (i = 0; i < qr->query->size; i++)
	{
		qr->operandData[i].operandexists = false;
		qr->operandData[i].reverseinsert = reverseinsert;
		qr->operandData[i].npos = 0;
	}
}