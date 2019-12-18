#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  hash; } ;
struct TYPE_13__ {int type; } ;
struct TYPE_10__ {int /*<<< orphan*/  len; int /*<<< orphan*/  val; } ;
struct TYPE_11__ {TYPE_1__ string; } ;
struct TYPE_12__ {TYPE_2__ val; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ JsonbValue ;
typedef  TYPE_4__ JsonPathItem ;
typedef  TYPE_5__ JsonPathGinPath ;

/* Variables and functions */
 int /*<<< orphan*/  JsonbHashScalarValue (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jbvString ; 
#define  jpiAnyArray 131 
#define  jpiIndexArray 130 
#define  jpiKey 129 
#define  jpiRoot 128 
 int /*<<< orphan*/  jspGetString (TYPE_4__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
jsonb_path_ops__add_path_item(JsonPathGinPath *path, JsonPathItem *jsp)
{
	switch (jsp->type)
	{
		case jpiRoot:
			path->hash = 0;		/* reset path hash */
			return true;

		case jpiKey:
			{
				JsonbValue	jbv;

				jbv.type = jbvString;
				jbv.val.string.val = jspGetString(jsp, &jbv.val.string.len);

				JsonbHashScalarValue(&jbv, &path->hash);
				return true;
			}

		case jpiIndexArray:
		case jpiAnyArray:
			return true;		/* path hash is unchanged */

		default:
			/* other items (wildcard paths, item methods) are not supported */
			return false;
	}
}