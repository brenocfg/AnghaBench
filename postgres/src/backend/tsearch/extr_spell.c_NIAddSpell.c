#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int nspell; int mspell; TYPE_2__** Spell; } ;
struct TYPE_7__ {int /*<<< orphan*/  flag; } ;
struct TYPE_8__ {TYPE_1__ p; int /*<<< orphan*/  word; } ;
typedef  TYPE_2__ SPELL ;
typedef  TYPE_3__ IspellDict ;

/* Variables and functions */
 int SPELLHDRSZ ; 
 int /*<<< orphan*/  VoidString ; 
 int /*<<< orphan*/  cpstrdup (TYPE_3__*,char const*) ; 
 scalar_t__ repalloc (TYPE_2__**,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 int strlen (char const*) ; 
 scalar_t__ tmpalloc (int) ; 

__attribute__((used)) static void
NIAddSpell(IspellDict *Conf, const char *word, const char *flag)
{
	if (Conf->nspell >= Conf->mspell)
	{
		if (Conf->mspell)
		{
			Conf->mspell *= 2;
			Conf->Spell = (SPELL **) repalloc(Conf->Spell, Conf->mspell * sizeof(SPELL *));
		}
		else
		{
			Conf->mspell = 1024 * 20;
			Conf->Spell = (SPELL **) tmpalloc(Conf->mspell * sizeof(SPELL *));
		}
	}
	Conf->Spell[Conf->nspell] = (SPELL *) tmpalloc(SPELLHDRSZ + strlen(word) + 1);
	strcpy(Conf->Spell[Conf->nspell]->word, word);
	Conf->Spell[Conf->nspell]->p.flag = (*flag != '\0')
		? cpstrdup(Conf, flag) : VoidString;
	Conf->nspell++;
}