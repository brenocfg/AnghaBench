#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  extnodename; } ;
typedef  TYPE_1__ ExtensibleNodeMethods ;

/* Variables and functions */
 int /*<<< orphan*/  RegisterExtensibleNodeEntry (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,TYPE_1__ const*) ; 
 int /*<<< orphan*/  extensible_node_methods ; 

void
RegisterExtensibleNodeMethods(const ExtensibleNodeMethods *methods)
{
	RegisterExtensibleNodeEntry(&extensible_node_methods,
								"Extensible Node Methods",
								methods->extnodename,
								methods);
}