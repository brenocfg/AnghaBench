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
typedef  int /*<<< orphan*/  int16 ;
typedef  int /*<<< orphan*/  TSQueryParserState ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  pushValue (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
pushval_asis(Datum opaque, TSQueryParserState state, char *strval, int lenval,
			 int16 weight, bool prefix)
{
	pushValue(state, strval, lenval, weight, prefix);
}