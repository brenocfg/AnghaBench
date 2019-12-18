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
typedef  int /*<<< orphan*/  ExtensibleNodeMethods ;

/* Variables and functions */
 scalar_t__ GetExtensibleNodeEntry (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  extensible_node_methods ; 

const ExtensibleNodeMethods *
GetExtensibleNodeMethods(const char *extnodename, bool missing_ok)
{
	return (const ExtensibleNodeMethods *)
		GetExtensibleNodeEntry(extensible_node_methods,
							   extnodename,
							   missing_ok);
}