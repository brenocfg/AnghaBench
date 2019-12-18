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
typedef  int Oid ;

/* Variables and functions */
 double DEFAULT_INEQ_SEL ; 
 double DEFAULT_RANGE_INEQ_SEL ; 
#define  OID_RANGE_CONTAINED_OP 140 
#define  OID_RANGE_CONTAINS_ELEM_OP 139 
#define  OID_RANGE_CONTAINS_OP 138 
#define  OID_RANGE_ELEM_CONTAINED_OP 137 
#define  OID_RANGE_GREATER_EQUAL_OP 136 
#define  OID_RANGE_GREATER_OP 135 
#define  OID_RANGE_LEFT_OP 134 
#define  OID_RANGE_LESS_EQUAL_OP 133 
#define  OID_RANGE_LESS_OP 132 
#define  OID_RANGE_OVERLAPS_LEFT_OP 131 
#define  OID_RANGE_OVERLAPS_RIGHT_OP 130 
#define  OID_RANGE_OVERLAP_OP 129 
#define  OID_RANGE_RIGHT_OP 128 

__attribute__((used)) static double
default_range_selectivity(Oid operator)
{
	switch (operator)
	{
		case OID_RANGE_OVERLAP_OP:
			return 0.01;

		case OID_RANGE_CONTAINS_OP:
		case OID_RANGE_CONTAINED_OP:
			return 0.005;

		case OID_RANGE_CONTAINS_ELEM_OP:
		case OID_RANGE_ELEM_CONTAINED_OP:

			/*
			 * "range @> elem" is more or less identical to a scalar
			 * inequality "A >= b AND A <= c".
			 */
			return DEFAULT_RANGE_INEQ_SEL;

		case OID_RANGE_LESS_OP:
		case OID_RANGE_LESS_EQUAL_OP:
		case OID_RANGE_GREATER_OP:
		case OID_RANGE_GREATER_EQUAL_OP:
		case OID_RANGE_LEFT_OP:
		case OID_RANGE_RIGHT_OP:
		case OID_RANGE_OVERLAPS_LEFT_OP:
		case OID_RANGE_OVERLAPS_RIGHT_OP:
			/* these are similar to regular scalar inequalities */
			return DEFAULT_INEQ_SEL;

		default:
			/* all range operators should be handled above, but just in case */
			return 0.01;
	}
}