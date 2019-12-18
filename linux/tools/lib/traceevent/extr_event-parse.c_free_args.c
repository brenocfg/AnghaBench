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
struct tep_print_arg {struct tep_print_arg* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_arg (struct tep_print_arg*) ; 

__attribute__((used)) static void free_args(struct tep_print_arg *args)
{
	struct tep_print_arg *next;

	while (args) {
		next = args->next;

		free_arg(args);
		args = next;
	}
}