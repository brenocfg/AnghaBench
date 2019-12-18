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
struct TYPE_7__ {int /*<<< orphan*/  extnodename; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* nodeOut ) (int /*<<< orphan*/ ,TYPE_2__ const*) ;} ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_1__ ExtensibleNodeMethods ;
typedef  TYPE_2__ ExtensibleNode ;

/* Variables and functions */
 TYPE_1__* GetExtensibleNodeMethods (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  WRITE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extnodename ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_2__ const*) ; 

__attribute__((used)) static void
_outExtensibleNode(StringInfo str, const ExtensibleNode *node)
{
	const ExtensibleNodeMethods *methods;

	methods = GetExtensibleNodeMethods(node->extnodename, false);

	WRITE_NODE_TYPE("EXTENSIBLENODE");

	WRITE_STRING_FIELD(extnodename);

	/* serialize the private fields */
	methods->nodeOut(str, node);
}