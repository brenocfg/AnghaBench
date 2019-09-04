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
typedef  void* u64 ;
struct sym_args {int started; void* start; int duplicate; void* size; scalar_t__ selected; } ;

/* Variables and functions */
 scalar_t__ kern_sym_match (struct sym_args*,char const*,char) ; 

__attribute__((used)) static int find_kern_sym_cb(void *arg, const char *name, char type, u64 start)
{
	struct sym_args *args = arg;

	if (args->started) {
		if (!args->size)
			args->size = start - args->start;
		if (args->selected) {
			if (args->size)
				return 1;
		} else if (kern_sym_match(args, name, type)) {
			args->duplicate = true;
			return 1;
		}
	} else if (kern_sym_match(args, name, type)) {
		args->started = true;
		args->start = start;
	}

	return 0;
}