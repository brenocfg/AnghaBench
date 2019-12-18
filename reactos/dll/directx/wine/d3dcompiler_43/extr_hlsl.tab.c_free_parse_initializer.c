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
struct parse_initializer {unsigned int args_count; int /*<<< orphan*/ * args; } ;

/* Variables and functions */
 int /*<<< orphan*/  d3dcompiler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_instr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_parse_initializer(struct parse_initializer *initializer)
{
    unsigned int i;
    for (i = 0; i < initializer->args_count; ++i)
        free_instr(initializer->args[i]);
    d3dcompiler_free(initializer->args);
}