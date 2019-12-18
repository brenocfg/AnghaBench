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
struct shader_func {TYPE_1__ params; int /*<<< orphan*/  mapping; int /*<<< orphan*/  return_type; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da_free (TYPE_1__) ; 
 int /*<<< orphan*/  shader_var_free (scalar_t__) ; 

__attribute__((used)) static inline void shader_func_free(struct shader_func *sf)
{
	size_t i;

	for (i = 0; i < sf->params.num; i++)
		shader_var_free(sf->params.array + i);

	bfree(sf->name);
	bfree(sf->return_type);
	bfree(sf->mapping);
	da_free(sf->params);
}