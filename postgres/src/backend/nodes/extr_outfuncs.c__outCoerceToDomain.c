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
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  CoerceToDomain ;

/* Variables and functions */
 int /*<<< orphan*/  CoercionForm ; 
 int /*<<< orphan*/  WRITE_ENUM_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_INT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_LOCATION_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  WRITE_OID_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arg ; 
 int /*<<< orphan*/  coercionformat ; 
 int /*<<< orphan*/  location ; 
 int /*<<< orphan*/  resultcollid ; 
 int /*<<< orphan*/  resulttype ; 
 int /*<<< orphan*/  resulttypmod ; 

__attribute__((used)) static void
_outCoerceToDomain(StringInfo str, const CoerceToDomain *node)
{
	WRITE_NODE_TYPE("COERCETODOMAIN");

	WRITE_NODE_FIELD(arg);
	WRITE_OID_FIELD(resulttype);
	WRITE_INT_FIELD(resulttypmod);
	WRITE_OID_FIELD(resultcollid);
	WRITE_ENUM_FIELD(coercionformat, CoercionForm);
	WRITE_LOCATION_FIELD(location);
}