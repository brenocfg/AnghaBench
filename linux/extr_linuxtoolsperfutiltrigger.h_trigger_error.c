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
struct trigger {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRIGGER_ERROR ; 

__attribute__((used)) static inline void trigger_error(struct trigger *t)
{
	t->state = TRIGGER_ERROR;
}