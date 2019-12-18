#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32 ;
struct TYPE_9__ {scalar_t__ replen; } ;
struct TYPE_8__ {int length; int isvoid; TYPE_1__* data; } ;
struct TYPE_7__ {int naffixes; TYPE_4__* Affix; TYPE_3__* Prefix; TYPE_3__* Suffix; } ;
struct TYPE_6__ {TYPE_4__** aff; scalar_t__ naff; TYPE_3__* node; } ;
typedef  TYPE_2__ IspellDict ;
typedef  int /*<<< orphan*/  AffixNodeData ;
typedef  TYPE_3__ AffixNode ;
typedef  TYPE_4__ AFFIX ;

/* Variables and functions */
 scalar_t__ ANHRDSZ ; 
 scalar_t__ cpalloc (int) ; 
 scalar_t__ palloc0 (scalar_t__) ; 

__attribute__((used)) static void
mkVoidAffix(IspellDict *Conf, bool issuffix, int startsuffix)
{
	int			i,
				cnt = 0;
	int			start = (issuffix) ? startsuffix : 0;
	int			end = (issuffix) ? Conf->naffixes : startsuffix;
	AffixNode  *Affix = (AffixNode *) palloc0(ANHRDSZ + sizeof(AffixNodeData));

	Affix->length = 1;
	Affix->isvoid = 1;

	if (issuffix)
	{
		Affix->data->node = Conf->Suffix;
		Conf->Suffix = Affix;
	}
	else
	{
		Affix->data->node = Conf->Prefix;
		Conf->Prefix = Affix;
	}

	/* Count affixes with empty replace string */
	for (i = start; i < end; i++)
		if (Conf->Affix[i].replen == 0)
			cnt++;

	/* There is not affixes with empty replace string */
	if (cnt == 0)
		return;

	Affix->data->aff = (AFFIX **) cpalloc(sizeof(AFFIX *) * cnt);
	Affix->data->naff = (uint32) cnt;

	cnt = 0;
	for (i = start; i < end; i++)
		if (Conf->Affix[i].replen == 0)
		{
			Affix->data->aff[cnt] = Conf->Affix + i;
			cnt++;
		}
}