#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char const* extnodename; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* nodeRead ) (TYPE_2__*) ;int /*<<< orphan*/  node_size; } ;
typedef  TYPE_1__ ExtensibleNodeMethods ;
typedef  TYPE_2__ ExtensibleNode ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 TYPE_1__* GetExtensibleNodeMethods (char const*,int) ; 
 int /*<<< orphan*/  READ_DONE () ; 
 int /*<<< orphan*/  READ_TEMP_LOCALS () ; 
 int /*<<< orphan*/  T_ExtensibleNode ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  length ; 
 scalar_t__ newNode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* nullable_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_strtok (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  token ; 

__attribute__((used)) static ExtensibleNode *
_readExtensibleNode(void)
{
	const ExtensibleNodeMethods *methods;
	ExtensibleNode *local_node;
	const char *extnodename;

	READ_TEMP_LOCALS();

	token = pg_strtok(&length); /* skip :extnodename */
	token = pg_strtok(&length); /* get extnodename */

	extnodename = nullable_string(token, length);
	if (!extnodename)
		elog(ERROR, "extnodename has to be supplied");
	methods = GetExtensibleNodeMethods(extnodename, false);

	local_node = (ExtensibleNode *) newNode(methods->node_size,
											T_ExtensibleNode);
	local_node->extnodename = extnodename;

	/* deserialize the private fields */
	methods->nodeRead(local_node);

	READ_DONE();
}