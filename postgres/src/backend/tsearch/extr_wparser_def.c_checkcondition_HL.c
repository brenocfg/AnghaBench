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
struct TYPE_6__ {int len; TYPE_1__* words; } ;
typedef  TYPE_2__ hlCheck ;
typedef  int /*<<< orphan*/  WordEntryPos ;
struct TYPE_7__ {scalar_t__* pos; int allocated; int npos; } ;
struct TYPE_5__ {scalar_t__ pos; int /*<<< orphan*/ * item; } ;
typedef  int /*<<< orphan*/  QueryOperand ;
typedef  TYPE_3__ ExecPhraseData ;

/* Variables and functions */
 scalar_t__* palloc (int) ; 

__attribute__((used)) static bool
checkcondition_HL(void *opaque, QueryOperand *val, ExecPhraseData *data)
{
	int			i;
	hlCheck    *checkval = (hlCheck *) opaque;

	for (i = 0; i < checkval->len; i++)
	{
		if (checkval->words[i].item == val)
		{
			/* don't need to find all positions */
			if (!data)
				return true;

			if (!data->pos)
			{
				data->pos = palloc(sizeof(WordEntryPos) * checkval->len);
				data->allocated = true;
				data->npos = 1;
				data->pos[0] = checkval->words[i].pos;
			}
			else if (data->pos[data->npos - 1] < checkval->words[i].pos)
			{
				data->pos[data->npos++] = checkval->words[i].pos;
			}
		}
	}

	if (data && data->npos > 0)
		return true;

	return false;
}