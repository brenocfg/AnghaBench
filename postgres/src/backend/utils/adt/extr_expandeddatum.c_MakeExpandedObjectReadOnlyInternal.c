#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ExpandedObjectHeader ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/ * DatumGetEOHP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EOHPGetRODatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VARATT_IS_EXTERNAL_EXPANDED_RW (int /*<<< orphan*/ ) ; 

Datum
MakeExpandedObjectReadOnlyInternal(Datum d)
{
	ExpandedObjectHeader *eohptr;

	/* Nothing to do if not a read-write expanded-object pointer */
	if (!VARATT_IS_EXTERNAL_EXPANDED_RW(DatumGetPointer(d)))
		return d;

	/* Now safe to extract the object pointer */
	eohptr = DatumGetEOHP(d);

	/* Return the built-in read-only pointer instead of given pointer */
	return EOHPGetRODatum(eohptr);
}