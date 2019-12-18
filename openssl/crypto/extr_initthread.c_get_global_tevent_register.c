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
typedef  int /*<<< orphan*/  GLOBAL_TEVENT_REGISTER ;

/* Variables and functions */
 int /*<<< orphan*/  RUN_ONCE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_global_tevent_register ; 
 int /*<<< orphan*/ * glob_tevent_reg ; 
 int /*<<< orphan*/  tevent_register_runonce ; 

__attribute__((used)) static GLOBAL_TEVENT_REGISTER *get_global_tevent_register(void)
{
    if (!RUN_ONCE(&tevent_register_runonce, create_global_tevent_register))
        return NULL;
    return glob_tevent_reg;
}