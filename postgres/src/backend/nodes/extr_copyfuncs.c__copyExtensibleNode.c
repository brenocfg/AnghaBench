#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  extnodename; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* nodeCopy ) (TYPE_2__*,TYPE_2__ const*) ;int /*<<< orphan*/  node_size; } ;
typedef  TYPE_1__ ExtensibleNodeMethods ;
typedef  TYPE_2__ ExtensibleNode ;

/* Variables and functions */
 int /*<<< orphan*/  COPY_STRING_FIELD (int /*<<< orphan*/ ) ; 
 TYPE_1__* GetExtensibleNodeMethods (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  T_ExtensibleNode ; 
 int /*<<< orphan*/  extnodename ; 
 scalar_t__ newNode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,TYPE_2__ const*) ; 

__attribute__((used)) static ExtensibleNode *
_copyExtensibleNode(const ExtensibleNode *from)
{
	ExtensibleNode *newnode;
	const ExtensibleNodeMethods *methods;

	methods = GetExtensibleNodeMethods(from->extnodename, false);
	newnode = (ExtensibleNode *) newNode(methods->node_size,
										 T_ExtensibleNode);
	COPY_STRING_FIELD(extnodename);

	/* copy the private fields */
	methods->nodeCopy(newnode, from);

	return newnode;
}