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
struct shader_var {int /*<<< orphan*/  default_val; int /*<<< orphan*/  mapping; int /*<<< orphan*/  name; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void shader_var_free(struct shader_var *sv)
{
	bfree(sv->type);
	bfree(sv->name);
	bfree(sv->mapping);
	da_free(sv->default_val);
}