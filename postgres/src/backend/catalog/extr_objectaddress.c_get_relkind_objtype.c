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
typedef  int /*<<< orphan*/  ObjectType ;

/* Variables and functions */
 int /*<<< orphan*/  OBJECT_FOREIGN_TABLE ; 
 int /*<<< orphan*/  OBJECT_INDEX ; 
 int /*<<< orphan*/  OBJECT_MATVIEW ; 
 int /*<<< orphan*/  OBJECT_SEQUENCE ; 
 int /*<<< orphan*/  OBJECT_TABLE ; 
 int /*<<< orphan*/  OBJECT_VIEW ; 
#define  RELKIND_FOREIGN_TABLE 136 
#define  RELKIND_INDEX 135 
#define  RELKIND_MATVIEW 134 
#define  RELKIND_PARTITIONED_INDEX 133 
#define  RELKIND_PARTITIONED_TABLE 132 
#define  RELKIND_RELATION 131 
#define  RELKIND_SEQUENCE 130 
#define  RELKIND_TOASTVALUE 129 
#define  RELKIND_VIEW 128 

ObjectType
get_relkind_objtype(char relkind)
{
	switch (relkind)
	{
		case RELKIND_RELATION:
		case RELKIND_PARTITIONED_TABLE:
			return OBJECT_TABLE;
		case RELKIND_INDEX:
		case RELKIND_PARTITIONED_INDEX:
			return OBJECT_INDEX;
		case RELKIND_SEQUENCE:
			return OBJECT_SEQUENCE;
		case RELKIND_VIEW:
			return OBJECT_VIEW;
		case RELKIND_MATVIEW:
			return OBJECT_MATVIEW;
		case RELKIND_FOREIGN_TABLE:
			return OBJECT_FOREIGN_TABLE;
		case RELKIND_TOASTVALUE:
			return OBJECT_TABLE;
		default:
			/* Per above, don't raise an error */
			return OBJECT_TABLE;
	}
}