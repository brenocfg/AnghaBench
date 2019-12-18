#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8 ;
struct TYPE_8__ {TYPE_2__* Dictionary; } ;
struct TYPE_7__ {int length; TYPE_1__* data; } ;
struct TYPE_6__ {scalar_t__ const val; int compoundflag; TYPE_2__* node; int /*<<< orphan*/  affix; scalar_t__ isword; } ;
typedef  TYPE_1__ SPNodeData ;
typedef  TYPE_2__ SPNode ;
typedef  TYPE_3__ IspellDict ;

/* Variables and functions */
 int FF_COMPOUNDFLAGMASK ; 
 int FF_COMPOUNDONLY ; 
 scalar_t__ IsAffixFlagInUse (TYPE_3__*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int
FindWord(IspellDict *Conf, const char *word, const char *affixflag, int flag)
{
	SPNode	   *node = Conf->Dictionary;
	SPNodeData *StopLow,
			   *StopHigh,
			   *StopMiddle;
	const uint8 *ptr = (const uint8 *) word;

	flag &= FF_COMPOUNDFLAGMASK;

	while (node && *ptr)
	{
		StopLow = node->data;
		StopHigh = node->data + node->length;
		while (StopLow < StopHigh)
		{
			StopMiddle = StopLow + ((StopHigh - StopLow) >> 1);
			if (StopMiddle->val == *ptr)
			{
				if (*(ptr + 1) == '\0' && StopMiddle->isword)
				{
					if (flag == 0)
					{
						/*
						 * The word can be formed only with another word. And
						 * in the flag parameter there is not a sign that we
						 * search compound words.
						 */
						if (StopMiddle->compoundflag & FF_COMPOUNDONLY)
							return 0;
					}
					else if ((flag & StopMiddle->compoundflag) == 0)
						return 0;

					/*
					 * Check if this affix rule is presented in the affix set
					 * with index StopMiddle->affix.
					 */
					if (IsAffixFlagInUse(Conf, StopMiddle->affix, affixflag))
						return 1;
				}
				node = StopMiddle->node;
				ptr++;
				break;
			}
			else if (StopMiddle->val < *ptr)
				StopLow = StopMiddle + 1;
			else
				StopHigh = StopMiddle;
		}
		if (StopLow >= StopHigh)
			break;
	}
	return 0;
}