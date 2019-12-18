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
struct TYPE_2__ {scalar_t__ scope_chain; int /*<<< orphan*/  code; } ;
typedef  TYPE_1__ InterpretedFunction ;
typedef  int /*<<< orphan*/  FunctionInstance ;

/* Variables and functions */
 int /*<<< orphan*/  release_bytecode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scope_release (scalar_t__) ; 

__attribute__((used)) static void InterpretedFunction_destructor(FunctionInstance *func)
{
    InterpretedFunction *function = (InterpretedFunction*)func;

    release_bytecode(function->code);
    if(function->scope_chain)
        scope_release(function->scope_chain);
}