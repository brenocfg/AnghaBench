#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * CompoundAffixFlags; int /*<<< orphan*/ * firstfree; int /*<<< orphan*/ * Spell; int /*<<< orphan*/ * buildCxt; } ;
typedef  TYPE_1__ IspellDict ;

/* Variables and functions */
 int /*<<< orphan*/  MemoryContextDelete (int /*<<< orphan*/ *) ; 

void
NIFinishBuild(IspellDict *Conf)
{
	/* Release no-longer-needed temp memory */
	MemoryContextDelete(Conf->buildCxt);
	/* Just for cleanliness, zero the now-dangling pointers */
	Conf->buildCxt = NULL;
	Conf->Spell = NULL;
	Conf->firstfree = NULL;
	Conf->CompoundAffixFlags = NULL;
}