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
struct TYPE_2__ {size_t num; struct ep_param* array; } ;
struct ep_param {TYPE_1__ annotations; TYPE_1__ properties; TYPE_1__ default_val; int /*<<< orphan*/  name; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da_free (TYPE_1__) ; 

__attribute__((used)) static inline void ep_param_free(struct ep_param *epp)
{
	bfree(epp->type);
	bfree(epp->name);
	da_free(epp->default_val);
	da_free(epp->properties);

	for (size_t i = 0; i < epp->annotations.num; i++)
		ep_param_free(epp->annotations.array + i);
	da_free(epp->annotations);
}