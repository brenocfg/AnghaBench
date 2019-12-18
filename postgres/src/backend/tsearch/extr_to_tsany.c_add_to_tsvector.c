#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32 ;
struct TYPE_5__ {int lenwords; scalar_t__ curwords; scalar_t__ pos; int /*<<< orphan*/ * words; } ;
struct TYPE_4__ {int /*<<< orphan*/  cfgId; TYPE_2__* prs; } ;
typedef  TYPE_1__ TSVectorBuildState ;
typedef  int /*<<< orphan*/  ParsedWord ;
typedef  TYPE_2__ ParsedText ;

/* Variables and functions */
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  parsetext (int /*<<< orphan*/ ,TYPE_2__*,char*,int) ; 

__attribute__((used)) static void
add_to_tsvector(void *_state, char *elem_value, int elem_len)
{
	TSVectorBuildState *state = (TSVectorBuildState *) _state;
	ParsedText *prs = state->prs;
	int32		prevwords;

	if (prs->words == NULL)
	{
		/*
		 * First time through: initialize words array to a reasonable size.
		 * (parsetext() will realloc it bigger as needed.)
		 */
		prs->lenwords = 16;
		prs->words = (ParsedWord *) palloc(sizeof(ParsedWord) * prs->lenwords);
		prs->curwords = 0;
		prs->pos = 0;
	}

	prevwords = prs->curwords;

	parsetext(state->cfgId, prs, elem_value, elem_len);

	/*
	 * If we extracted any words from this JSON element, advance pos to create
	 * an artificial break between elements.  This is because we don't want
	 * phrase searches to think that the last word in this element is adjacent
	 * to the first word in the next one.
	 */
	if (prs->curwords > prevwords)
		prs->pos += 1;
}