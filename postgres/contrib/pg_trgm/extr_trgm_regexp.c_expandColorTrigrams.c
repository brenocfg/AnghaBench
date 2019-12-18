#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  bytes; } ;
typedef  TYPE_2__ trgm_mb_char ;
typedef  int /*<<< orphan*/  trgm ;
struct TYPE_14__ {int totalTrgmCount; int colorTrgmsCount; TYPE_4__* colorInfo; TYPE_6__* colorTrgms; } ;
typedef  TYPE_3__ TrgmNFA ;
struct TYPE_15__ {int wordCharsCount; TYPE_2__* wordChars; } ;
typedef  TYPE_4__ TrgmColorInfo ;
struct TYPE_12__ {size_t* colors; } ;
struct TYPE_17__ {TYPE_1__ ctrgm; int /*<<< orphan*/  expanded; } ;
struct TYPE_16__ {int /*<<< orphan*/  flag; } ;
typedef  TYPE_5__ TRGM ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_6__ ColorTrgmInfo ;

/* Variables and functions */
 int /*<<< orphan*/  ARRKEY ; 
 int /*<<< orphan*/  CALCGTSIZE (int /*<<< orphan*/ ,int) ; 
 size_t COLOR_BLANK ; 
 int /*<<< orphan*/ * GETARR (TYPE_5__*) ; 
 scalar_t__ MemoryContextAllocZero (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SET_VARSIZE (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ TRGMHDRSIZE ; 
 int /*<<< orphan*/  fillTrgm (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static TRGM *
expandColorTrigrams(TrgmNFA *trgmNFA, MemoryContext rcontext)
{
	TRGM	   *trg;
	trgm	   *p;
	int			i;
	TrgmColorInfo blankColor;
	trgm_mb_char blankChar;

	/* Set up "blank" color structure containing a single zero character */
	memset(blankChar.bytes, 0, sizeof(blankChar.bytes));
	blankColor.wordCharsCount = 1;
	blankColor.wordChars = &blankChar;

	/* Construct the trgm array */
	trg = (TRGM *)
		MemoryContextAllocZero(rcontext,
							   TRGMHDRSIZE +
							   trgmNFA->totalTrgmCount * sizeof(trgm));
	trg->flag = ARRKEY;
	SET_VARSIZE(trg, CALCGTSIZE(ARRKEY, trgmNFA->totalTrgmCount));
	p = GETARR(trg);
	for (i = 0; i < trgmNFA->colorTrgmsCount; i++)
	{
		ColorTrgmInfo *colorTrgm = &trgmNFA->colorTrgms[i];
		TrgmColorInfo *c[3];
		trgm_mb_char s[3];
		int			j,
					i1,
					i2,
					i3;

		/* Ignore any unexpanded trigrams ... */
		if (!colorTrgm->expanded)
			continue;

		/* Get colors, substituting the dummy struct for COLOR_BLANK */
		for (j = 0; j < 3; j++)
		{
			if (colorTrgm->ctrgm.colors[j] != COLOR_BLANK)
				c[j] = &trgmNFA->colorInfo[colorTrgm->ctrgm.colors[j]];
			else
				c[j] = &blankColor;
		}

		/* Iterate over all possible combinations of colors' characters */
		for (i1 = 0; i1 < c[0]->wordCharsCount; i1++)
		{
			s[0] = c[0]->wordChars[i1];
			for (i2 = 0; i2 < c[1]->wordCharsCount; i2++)
			{
				s[1] = c[1]->wordChars[i2];
				for (i3 = 0; i3 < c[2]->wordCharsCount; i3++)
				{
					s[2] = c[2]->wordChars[i3];
					fillTrgm(p, s);
					p++;
				}
			}
		}
	}

	return trg;
}