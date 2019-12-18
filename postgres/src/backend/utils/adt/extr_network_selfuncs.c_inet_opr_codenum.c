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
 int /*<<< orphan*/  ERROR ; 
#define  OID_INET_OVERLAP_OP 132 
#define  OID_INET_SUBEQ_OP 131 
#define  OID_INET_SUB_OP 130 
#define  OID_INET_SUPEQ_OP 129 
#define  OID_INET_SUP_OP 128 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
inet_opr_codenum(Oid operator)
{
	switch (operator)
	{
		case OID_INET_SUP_OP:
			return -2;
		case OID_INET_SUPEQ_OP:
			return -1;
		case OID_INET_OVERLAP_OP:
			return 0;
		case OID_INET_SUBEQ_OP:
			return 1;
		case OID_INET_SUB_OP:
			return 2;
		default:
			elog(ERROR, "unrecognized operator %u for inet selectivity",
				 operator);
	}
	return 0;					/* unreached, but keep compiler quiet */
}