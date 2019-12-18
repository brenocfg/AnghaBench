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
struct scripting_ops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ script_spec_register (char*,struct scripting_ops*) ; 
 int /*<<< orphan*/ * scripting_context ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ **) ; 

__attribute__((used)) static void register_python_scripting(struct scripting_ops *scripting_ops)
{
	if (scripting_context == NULL)
		scripting_context = malloc(sizeof(*scripting_context));

       if (scripting_context == NULL ||
	   script_spec_register("Python", scripting_ops) ||
	   script_spec_register("py", scripting_ops)) {
		pr_err("Error registering Python script extension: disabling it\n");
		zfree(&scripting_context);
	}
}