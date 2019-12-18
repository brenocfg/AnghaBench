#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_4__ {int nAffixData; int /*<<< orphan*/ * AffixData; } ;
typedef  TYPE_1__ IspellDict ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int FF_COMPOUNDFLAGMASK ; 
 int getCompoundAffixFlagValue (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32
makeCompoundFlags(IspellDict *Conf, int affix)
{
	Assert(affix < Conf->nAffixData);

	return (getCompoundAffixFlagValue(Conf, Conf->AffixData[affix]) &
			FF_COMPOUNDFLAGMASK);
}