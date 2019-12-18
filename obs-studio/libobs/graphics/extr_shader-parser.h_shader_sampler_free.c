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
struct TYPE_2__ {size_t num; int /*<<< orphan*/ * array; } ;
struct shader_sampler {TYPE_1__ values; TYPE_1__ states; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da_free (TYPE_1__) ; 

__attribute__((used)) static inline void shader_sampler_free(struct shader_sampler *ss)
{
	size_t i;
	for (i = 0; i < ss->states.num; i++)
		bfree(ss->states.array[i]);
	for (i = 0; i < ss->values.num; i++)
		bfree(ss->values.array[i]);

	bfree(ss->name);
	da_free(ss->states);
	da_free(ss->values);
}