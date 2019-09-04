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
 int /*<<< orphan*/  XSI_NAMESPACE ; 
 int /*<<< orphan*/  set_ns_prop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void set_xsi_type(xmlNodePtr node, char *type)
{
	set_ns_prop(node, XSI_NAMESPACE, "type", type);
}