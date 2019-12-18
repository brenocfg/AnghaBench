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
struct TYPE_4__ {int /*<<< orphan*/  model; } ;
typedef  TYPE_1__ CPU_MODEL ;

/* Variables and functions */
 TYPE_1__* __get_cpu_model_recursive (char*) ; 
 int /*<<< orphan*/  r_str_casecmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CPU_MODEL *get_cpu_model(char *model) {
	static CPU_MODEL *cpu = NULL;
	// cached value?
	if (cpu && !r_str_casecmp (model, cpu->model)) {
		return cpu;
	}
	// do the real search
	cpu = __get_cpu_model_recursive (model);
	return cpu;
}