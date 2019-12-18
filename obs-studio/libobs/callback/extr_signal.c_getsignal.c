#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct signal_info {struct signal_info* next; TYPE_1__ func; } ;
struct TYPE_5__ {struct signal_info* first; } ;
typedef  TYPE_2__ signal_handler_t ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static struct signal_info *getsignal(signal_handler_t *handler,
				     const char *name,
				     struct signal_info **p_last)
{
	struct signal_info *signal, *last = NULL;

	signal = handler->first;
	while (signal != NULL) {
		if (strcmp(signal->func.name, name) == 0)
			break;

		last = signal;
		signal = signal->next;
	}

	if (p_last)
		*p_last = last;
	return signal;
}