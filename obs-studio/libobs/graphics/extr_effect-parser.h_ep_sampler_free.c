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
struct ep_sampler {TYPE_1__ values; TYPE_1__ states; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da_free (TYPE_1__) ; 

__attribute__((used)) static inline void ep_sampler_free(struct ep_sampler *eps)
{
	size_t i;

	for (i = 0; i < eps->states.num; i++)
		bfree(eps->states.array[i]);
	for (i = 0; i < eps->values.num; i++)
		bfree(eps->values.array[i]);

	bfree(eps->name);
	da_free(eps->states);
	da_free(eps->values);
}