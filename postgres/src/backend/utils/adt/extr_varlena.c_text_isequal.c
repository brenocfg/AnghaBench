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
typedef  int /*<<< orphan*/  text ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int DatumGetBool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall2Coll (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  texteq ; 

__attribute__((used)) static bool
text_isequal(text *txt1, text *txt2, Oid collid)
{
	return DatumGetBool(DirectFunctionCall2Coll(texteq,
												collid,
												PointerGetDatum(txt1),
												PointerGetDatum(txt2)));
}