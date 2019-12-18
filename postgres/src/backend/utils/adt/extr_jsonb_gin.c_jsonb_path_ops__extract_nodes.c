#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_3__ {int /*<<< orphan*/  hash; } ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  JsonbValue ;
typedef  TYPE_1__ JsonPathGinPath ;
typedef  int /*<<< orphan*/  JsonPathGinContext ;

/* Variables and functions */
 int /*<<< orphan*/  JsonbHashScalarValue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UInt32GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_jsp_entry_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static List *
jsonb_path_ops__extract_nodes(JsonPathGinContext *cxt, JsonPathGinPath path,
							  JsonbValue *scalar, List *nodes)
{
	if (scalar)
	{
		/* append path hash node for equality queries */
		uint32		hash = path.hash;

		JsonbHashScalarValue(scalar, &hash);

		return lappend(nodes,
					   make_jsp_entry_node(UInt32GetDatum(hash)));
	}
	else
	{
		/* jsonb_path_ops doesn't support EXISTS queries => nothing to append */
		return nodes;
	}
}