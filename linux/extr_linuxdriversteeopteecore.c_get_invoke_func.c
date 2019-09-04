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
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  optee_invoke_fn ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/ * ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ of_property_read_string (struct device_node*,char*,char const**) ; 
 int /*<<< orphan*/ * optee_smccc_hvc ; 
 int /*<<< orphan*/ * optee_smccc_smc ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 

__attribute__((used)) static optee_invoke_fn *get_invoke_func(struct device_node *np)
{
	const char *method;

	pr_info("probing for conduit method from DT.\n");

	if (of_property_read_string(np, "method", &method)) {
		pr_warn("missing \"method\" property\n");
		return ERR_PTR(-ENXIO);
	}

	if (!strcmp("hvc", method))
		return optee_smccc_hvc;
	else if (!strcmp("smc", method))
		return optee_smccc_smc;

	pr_warn("invalid \"method\" property: %s\n", method);
	return ERR_PTR(-EINVAL);
}