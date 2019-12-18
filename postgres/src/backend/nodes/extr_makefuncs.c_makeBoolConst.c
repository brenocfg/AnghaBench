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
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  BOOLOID ; 
 int /*<<< orphan*/  BoolGetDatum (int) ; 
 int /*<<< orphan*/  InvalidOid ; 
 scalar_t__ makeConst (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 

Node *
makeBoolConst(bool value, bool isnull)
{
	/* note that pg_type.h hardwires size of bool as 1 ... duplicate it */
	return (Node *) makeConst(BOOLOID, -1, InvalidOid, 1,
							  BoolGetDatum(value), isnull, true);
}