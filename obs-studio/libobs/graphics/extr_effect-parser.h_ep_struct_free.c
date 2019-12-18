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
struct TYPE_2__ {size_t num; scalar_t__ array; } ;
struct ep_struct {TYPE_1__ vars; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da_free (TYPE_1__) ; 
 int /*<<< orphan*/  ep_var_free (scalar_t__) ; 

__attribute__((used)) static inline void ep_struct_free(struct ep_struct *eps)
{
	size_t i;

	bfree(eps->name);
	for (i = 0; i < eps->vars.num; i++)
		ep_var_free(eps->vars.array + i);
	da_free(eps->vars);
}