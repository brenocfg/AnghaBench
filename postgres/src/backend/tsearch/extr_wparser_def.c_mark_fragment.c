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
struct TYPE_5__ {TYPE_1__* words; } ;
struct TYPE_4__ {int selected; int replace; int skip; int in; scalar_t__ repeated; int /*<<< orphan*/  type; scalar_t__ item; } ;
typedef  TYPE_2__ HeadlineParsedText ;

/* Variables and functions */
 scalar_t__ HLIDREPLACE (int /*<<< orphan*/ ) ; 
 scalar_t__ HLIDSKIP (int /*<<< orphan*/ ) ; 
 scalar_t__ XMLHLIDSKIP (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mark_fragment(HeadlineParsedText *prs, int highlight, int startpos, int endpos)
{
	int			i;

	for (i = startpos; i <= endpos; i++)
	{
		if (prs->words[i].item)
			prs->words[i].selected = 1;
		if (highlight == 0)
		{
			if (HLIDREPLACE(prs->words[i].type))
				prs->words[i].replace = 1;
			else if (HLIDSKIP(prs->words[i].type))
				prs->words[i].skip = 1;
		}
		else
		{
			if (XMLHLIDSKIP(prs->words[i].type))
				prs->words[i].skip = 1;
		}

		prs->words[i].in = (prs->words[i].repeated) ? 0 : 1;
	}
}