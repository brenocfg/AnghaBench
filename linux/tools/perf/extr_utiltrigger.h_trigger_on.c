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
 int /*<<< orphan*/  TRIGGER_OFF ; 
 int /*<<< orphan*/  TRIGGER_ON ; 
 int /*<<< orphan*/  TRIGGER_WARN_ONCE (struct trigger*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void trigger_on(struct trigger *t)
{
	TRIGGER_WARN_ONCE(t, TRIGGER_OFF);
	t->state = TRIGGER_ON;
}