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
struct field_var {int /*<<< orphan*/  val; int /*<<< orphan*/  var; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_hist_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct field_var*) ; 

__attribute__((used)) static void destroy_field_var(struct field_var *field_var)
{
	if (!field_var)
		return;

	destroy_hist_field(field_var->var, 0);
	destroy_hist_field(field_var->val, 0);

	kfree(field_var);
}