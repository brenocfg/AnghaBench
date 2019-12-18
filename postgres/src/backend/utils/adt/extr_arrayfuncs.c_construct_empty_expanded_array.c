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
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  ExpandedArrayHeader ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  ArrayType ;
typedef  int /*<<< orphan*/  ArrayMetaState ;

/* Variables and functions */
 scalar_t__ DatumGetEOHP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * construct_empty_array (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 

ExpandedArrayHeader *
construct_empty_expanded_array(Oid element_type,
							   MemoryContext parentcontext,
							   ArrayMetaState *metacache)
{
	ArrayType  *array = construct_empty_array(element_type);
	Datum		d;

	d = expand_array(PointerGetDatum(array), parentcontext, metacache);
	pfree(array);
	return (ExpandedArrayHeader *) DatumGetEOHP(d);
}