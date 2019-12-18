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
struct module {int /*<<< orphan*/  imported_namespaces; } ;

/* Variables and functions */
 int contains_namespace (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static bool module_imports_namespace(struct module *module,
				     const char *namespace)
{
	return contains_namespace(module->imported_namespaces, namespace);
}