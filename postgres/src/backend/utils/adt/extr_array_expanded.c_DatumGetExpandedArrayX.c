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
struct TYPE_7__ {int /*<<< orphan*/  typalign; int /*<<< orphan*/  typbyval; int /*<<< orphan*/  typlen; int /*<<< orphan*/  element_type; } ;
struct TYPE_6__ {scalar_t__ ea_magic; int /*<<< orphan*/  typalign; int /*<<< orphan*/  typbyval; int /*<<< orphan*/  typlen; int /*<<< orphan*/  element_type; } ;
typedef  TYPE_1__ ExpandedArrayHeader ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_2__ ArrayMetaState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 scalar_t__ DatumGetEOHP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetPointer (int /*<<< orphan*/ ) ; 
 scalar_t__ EA_MAGIC ; 
 scalar_t__ VARATT_IS_EXTERNAL_EXPANDED_RW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 

ExpandedArrayHeader *
DatumGetExpandedArrayX(Datum d, ArrayMetaState *metacache)
{
	/* If it's a writable expanded array already, just return it */
	if (VARATT_IS_EXTERNAL_EXPANDED_RW(DatumGetPointer(d)))
	{
		ExpandedArrayHeader *eah = (ExpandedArrayHeader *) DatumGetEOHP(d);

		Assert(eah->ea_magic == EA_MAGIC);
		/* Update cache if provided */
		if (metacache)
		{
			metacache->element_type = eah->element_type;
			metacache->typlen = eah->typlen;
			metacache->typbyval = eah->typbyval;
			metacache->typalign = eah->typalign;
		}
		return eah;
	}

	/* Else expand using caller's cache if any */
	d = expand_array(d, CurrentMemoryContext, metacache);
	return (ExpandedArrayHeader *) DatumGetEOHP(d);
}