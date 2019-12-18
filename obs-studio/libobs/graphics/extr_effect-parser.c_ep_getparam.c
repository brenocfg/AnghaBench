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
struct ep_param {int /*<<< orphan*/  name; } ;
struct TYPE_2__ {size_t num; struct ep_param* array; } ;
struct effect_parser {TYPE_1__ params; } ;

/* Variables and functions */
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct ep_param *ep_getparam(struct effect_parser *ep,
					   const char *name)
{
	size_t i;
	for (i = 0; i < ep->params.num; i++) {
		if (strcmp(name, ep->params.array[i].name) == 0)
			return ep->params.array + i;
	}

	return NULL;
}