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
typedef  int /*<<< orphan*/  TypeName ;
typedef  int /*<<< orphan*/  Type ;
typedef  int /*<<< orphan*/  ParseState ;

/* Variables and functions */
 int /*<<< orphan*/  LookupTypeNameExtended (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int,int) ; 

Type
LookupTypeName(ParseState *pstate, const TypeName *typeName,
			   int32 *typmod_p, bool missing_ok)
{
	return LookupTypeNameExtended(pstate,
								  typeName, typmod_p, true, missing_ok);
}