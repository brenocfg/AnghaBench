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
typedef  int /*<<< orphan*/  xmlNodePtr ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_CAST (char*) ; 
 int /*<<< orphan*/  encode_add_ns (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xmlSetNsProp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_ns_prop(xmlNodePtr node, char *ns, char *name, char *val)
{
	xmlSetNsProp(node, encode_add_ns(node, ns), BAD_CAST(name), BAD_CAST(val));
}