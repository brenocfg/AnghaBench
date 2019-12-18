#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int float4 ;
struct TYPE_11__ {double frequency; int /*<<< orphan*/  element; } ;
typedef  TYPE_2__ TextFreq ;
struct TYPE_14__ {char* lexeme; int length; } ;
struct TYPE_10__ {int oper; int /*<<< orphan*/  left; } ;
struct TYPE_13__ {scalar_t__ type; TYPE_1__ qoperator; } ;
struct TYPE_12__ {int distance; int length; scalar_t__ prefix; } ;
typedef  double Selectivity ;
typedef  TYPE_3__ QueryOperand ;
typedef  TYPE_4__ QueryItem ;
typedef  TYPE_5__ LexemeKey ;

/* Variables and functions */
 int /*<<< orphan*/  CLAMP_PROBABILITY (double) ; 
 int DEFAULT_TS_MATCH_SEL ; 
 int /*<<< orphan*/  ERROR ; 
 double Max (double,double) ; 
 double Min (int,int) ; 
#define  OP_AND 131 
#define  OP_NOT 130 
#define  OP_OR 129 
#define  OP_PHRASE 128 
 scalar_t__ QI_VAL ; 
 int /*<<< orphan*/  VARDATA_ANY (int /*<<< orphan*/ ) ; 
 int VARSIZE_ANY_EXHDR (int /*<<< orphan*/ ) ; 
 scalar_t__ bsearch (TYPE_5__*,TYPE_2__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_stack_depth () ; 
 int /*<<< orphan*/  compare_lexeme_textfreq ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static Selectivity
tsquery_opr_selec(QueryItem *item, char *operand,
				  TextFreq *lookup, int length, float4 minfreq)
{
	Selectivity selec;

	/* since this function recurses, it could be driven to stack overflow */
	check_stack_depth();

	if (item->type == QI_VAL)
	{
		QueryOperand *oper = (QueryOperand *) item;
		LexemeKey	key;

		/*
		 * Prepare the key for bsearch().
		 */
		key.lexeme = operand + oper->distance;
		key.length = oper->length;

		if (oper->prefix)
		{
			/* Prefix match, ie the query item is lexeme:* */
			Selectivity matched,
						allmces;
			int			i,
						n_matched;

			/*
			 * Our strategy is to scan through the MCELEM list and combine the
			 * frequencies of the ones that match the prefix.  We then
			 * extrapolate the fraction of matching MCELEMs to the remaining
			 * rows, assuming that the MCELEMs are representative of the whole
			 * lexeme population in this respect.  (Compare
			 * histogram_selectivity().)  Note that these are most common
			 * elements not most common values, so they're not mutually
			 * exclusive.  We treat occurrences as independent events.
			 *
			 * This is only a good plan if we have a pretty fair number of
			 * MCELEMs available; we set the threshold at 100.  If no stats or
			 * insufficient stats, arbitrarily use DEFAULT_TS_MATCH_SEL*4.
			 */
			if (lookup == NULL || length < 100)
				return (Selectivity) (DEFAULT_TS_MATCH_SEL * 4);

			matched = allmces = 0;
			n_matched = 0;
			for (i = 0; i < length; i++)
			{
				TextFreq   *t = lookup + i;
				int			tlen = VARSIZE_ANY_EXHDR(t->element);

				if (tlen >= key.length &&
					strncmp(key.lexeme, VARDATA_ANY(t->element),
							key.length) == 0)
				{
					matched += t->frequency - matched * t->frequency;
					n_matched++;
				}
				allmces += t->frequency - allmces * t->frequency;
			}

			/* Clamp to ensure sanity in the face of roundoff error */
			CLAMP_PROBABILITY(matched);
			CLAMP_PROBABILITY(allmces);

			selec = matched + (1.0 - allmces) * ((double) n_matched / length);

			/*
			 * In any case, never believe that a prefix match has selectivity
			 * less than we would assign for a non-MCELEM lexeme.  This
			 * preserves the property that "word:*" should be estimated to
			 * match at least as many rows as "word" would be.
			 */
			selec = Max(Min(DEFAULT_TS_MATCH_SEL, minfreq / 2), selec);
		}
		else
		{
			/* Regular exact lexeme match */
			TextFreq   *searchres;

			/* If no stats for the variable, use DEFAULT_TS_MATCH_SEL */
			if (lookup == NULL)
				return (Selectivity) DEFAULT_TS_MATCH_SEL;

			searchres = (TextFreq *) bsearch(&key, lookup, length,
											 sizeof(TextFreq),
											 compare_lexeme_textfreq);

			if (searchres)
			{
				/*
				 * The element is in MCELEM.  Return precise selectivity (or
				 * at least as precise as ANALYZE could find out).
				 */
				selec = searchres->frequency;
			}
			else
			{
				/*
				 * The element is not in MCELEM.  Punt, but assume that the
				 * selectivity cannot be more than minfreq / 2.
				 */
				selec = Min(DEFAULT_TS_MATCH_SEL, minfreq / 2);
			}
		}
	}
	else
	{
		/* Current TSQuery node is an operator */
		Selectivity s1,
					s2;

		switch (item->qoperator.oper)
		{
			case OP_NOT:
				selec = 1.0 - tsquery_opr_selec(item + 1, operand,
												lookup, length, minfreq);
				break;

			case OP_PHRASE:
			case OP_AND:
				s1 = tsquery_opr_selec(item + 1, operand,
									   lookup, length, minfreq);
				s2 = tsquery_opr_selec(item + item->qoperator.left, operand,
									   lookup, length, minfreq);
				selec = s1 * s2;
				break;

			case OP_OR:
				s1 = tsquery_opr_selec(item + 1, operand,
									   lookup, length, minfreq);
				s2 = tsquery_opr_selec(item + item->qoperator.left, operand,
									   lookup, length, minfreq);
				selec = s1 + s2 - s1 * s2;
				break;

			default:
				elog(ERROR, "unrecognized operator: %d", item->qoperator.oper);
				selec = 0;		/* keep compiler quiet */
				break;
		}
	}

	/* Clamp intermediate results to stay sane despite roundoff error */
	CLAMP_PROBABILITY(selec);

	return selec;
}