#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* lexeme; int /*<<< orphan*/ * entries; } ;
typedef  TYPE_1__ TheLexeme ;
struct TYPE_7__ {int /*<<< orphan*/  nwrds; int /*<<< orphan*/  wrds; } ;
typedef  int /*<<< orphan*/  LexemeInfo ;
typedef  TYPE_2__ DictThesaurus ;

/* Variables and functions */
 TYPE_1__* bsearch (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmpLexemeQ ; 

__attribute__((used)) static LexemeInfo *
findTheLexeme(DictThesaurus *d, char *lexeme)
{
	TheLexeme	key,
			   *res;

	if (d->nwrds == 0)
		return NULL;

	key.lexeme = lexeme;
	key.entries = NULL;

	res = bsearch(&key, d->wrds, d->nwrds, sizeof(TheLexeme), cmpLexemeQ);

	if (res == NULL)
		return NULL;
	return res->entries;
}