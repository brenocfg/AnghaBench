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
typedef  int /*<<< orphan*/  int32 ;
typedef  scalar_t__ int16 ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  Const ;

/* Variables and functions */
 int /*<<< orphan*/  get_typlenbyval (int /*<<< orphan*/ ,scalar_t__*,int*) ; 
 int /*<<< orphan*/ * makeConst (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 

Const *
makeNullConst(Oid consttype, int32 consttypmod, Oid constcollid)
{
	int16		typLen;
	bool		typByVal;

	get_typlenbyval(consttype, &typLen, &typByVal);
	return makeConst(consttype,
					 consttypmod,
					 constcollid,
					 (int) typLen,
					 (Datum) 0,
					 true,
					 typByVal);
}