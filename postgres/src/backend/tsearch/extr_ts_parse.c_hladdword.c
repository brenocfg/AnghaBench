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
typedef  scalar_t__ uint8 ;
struct TYPE_6__ {size_t curwords; size_t lenwords; TYPE_1__* words; } ;
struct TYPE_5__ {int len; int /*<<< orphan*/  word; scalar_t__ type; } ;
typedef  TYPE_1__ HeadlineWordEntry ;
typedef  TYPE_2__ HeadlineParsedText ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  palloc (int) ; 
 scalar_t__ repalloc (void*,int) ; 

__attribute__((used)) static void
hladdword(HeadlineParsedText *prs, char *buf, int buflen, int type)
{
	while (prs->curwords >= prs->lenwords)
	{
		prs->lenwords *= 2;
		prs->words = (HeadlineWordEntry *) repalloc((void *) prs->words, prs->lenwords * sizeof(HeadlineWordEntry));
	}
	memset(&(prs->words[prs->curwords]), 0, sizeof(HeadlineWordEntry));
	prs->words[prs->curwords].type = (uint8) type;
	prs->words[prs->curwords].len = buflen;
	prs->words[prs->curwords].word = palloc(buflen);
	memcpy(prs->words[prs->curwords].word, buf, buflen);
	prs->curwords++;
}