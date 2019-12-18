#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * addr; scalar_t__ name; } ;

/* Variables and functions */
 int NUM_TRACED_VARIABLES ; 
 scalar_t__ strcmp_P (char const*,scalar_t__) ; 
 TYPE_1__* traced_variables ; 
 int /*<<< orphan*/  verify_traced_variables (char const*,int) ; 

void remove_traced_variable(const char* name, const char* func, int line) {
    verify_traced_variables(func, line);
    for (int i = 0; i < NUM_TRACED_VARIABLES; i++) {
        if (strcmp_P(name, traced_variables[i].name) == 0) {
            traced_variables[i].name = 0;
            traced_variables[i].addr = NULL;
            break;
        }
    }
}