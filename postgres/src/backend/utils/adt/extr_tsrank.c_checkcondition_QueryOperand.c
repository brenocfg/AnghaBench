#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  pos; scalar_t__ npos; } ;
struct TYPE_5__ {scalar_t__ npos; scalar_t__ reverseinsert; int /*<<< orphan*/  pos; int /*<<< orphan*/  operandexists; } ;
typedef  TYPE_1__ QueryRepresentationOperand ;
typedef  int /*<<< orphan*/  QueryRepresentation ;
typedef  int /*<<< orphan*/  QueryOperand ;
typedef  TYPE_2__ ExecPhraseData ;

/* Variables and functions */
 scalar_t__ MAXQROPOS ; 
 TYPE_1__* QR_GET_OPERAND_DATA (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
checkcondition_QueryOperand(void *checkval, QueryOperand *val, ExecPhraseData *data)
{
	QueryRepresentation *qr = (QueryRepresentation *) checkval;
	QueryRepresentationOperand *opData = QR_GET_OPERAND_DATA(qr, val);

	if (!opData->operandexists)
		return false;

	if (data)
	{
		data->npos = opData->npos;
		data->pos = opData->pos;
		if (opData->reverseinsert)
			data->pos += MAXQROPOS - opData->npos;
	}

	return true;
}