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
struct trigger {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ TRIGGER_ERROR ; 

__attribute__((used)) static inline bool trigger_is_error(struct trigger *t)
{
	return t->state <= TRIGGER_ERROR;
}