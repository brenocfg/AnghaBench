#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int typid; } ;
struct TYPE_6__ {int /*<<< orphan*/  data; } ;
struct TYPE_8__ {TYPE_2__ datetime; TYPE_1__ binary; } ;
struct TYPE_9__ {int type; TYPE_3__ val; } ;
typedef  TYPE_4__ JsonbValue ;

/* Variables and functions */
#define  DATEOID 140 
 int /*<<< orphan*/  ERROR ; 
 char const* JsonbContainerTypeName (int /*<<< orphan*/ ) ; 
#define  TIMEOID 139 
#define  TIMESTAMPOID 138 
#define  TIMESTAMPTZOID 137 
#define  TIMETZOID 136 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
#define  jbvArray 135 
#define  jbvBinary 134 
#define  jbvBool 133 
#define  jbvDatetime 132 
#define  jbvNull 131 
#define  jbvNumeric 130 
#define  jbvObject 129 
#define  jbvString 128 

const char *
JsonbTypeName(JsonbValue *jbv)
{
	switch (jbv->type)
	{
		case jbvBinary:
			return JsonbContainerTypeName(jbv->val.binary.data);
		case jbvObject:
			return "object";
		case jbvArray:
			return "array";
		case jbvNumeric:
			return "number";
		case jbvString:
			return "string";
		case jbvBool:
			return "boolean";
		case jbvNull:
			return "null";
		case jbvDatetime:
			switch (jbv->val.datetime.typid)
			{
				case DATEOID:
					return "date";
				case TIMEOID:
					return "time without time zone";
				case TIMETZOID:
					return "time with time zone";
				case TIMESTAMPOID:
					return "timestamp without time zone";
				case TIMESTAMPTZOID:
					return "timestamp with time zone";
				default:
					elog(ERROR, "unrecognized jsonb value datetime type: %d",
						 jbv->val.datetime.typid);
			}
			return "unknown";
		default:
			elog(ERROR, "unrecognized jsonb value type: %d", jbv->type);
			return "unknown";
	}
}