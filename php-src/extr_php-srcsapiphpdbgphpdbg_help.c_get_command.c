#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char const alias; scalar_t__ name; } ;
typedef  TYPE_1__ phpdbg_command_t ;

/* Variables and functions */
 int /*<<< orphan*/  strncmp (scalar_t__,char const*,size_t) ; 

__attribute__((used)) static int get_command(
	const char *key, size_t len,      /* pointer and length of key */
	phpdbg_command_t const **command, /* address of first matching command  */
	phpdbg_command_t const * commands /* command table to be scanned */
	)
{
	const phpdbg_command_t *c;
	unsigned int num_matches = 0;

	if (len == 1) {
		for (c=commands; c->name; c++) {
			if (c->alias == key[0]) {
				num_matches++;
				if ( num_matches == 1 && command) {
					*command = c;
				}
			}
		}
	} else {
		for (c=commands; c->name; c++) {
			if (!strncmp(c->name, key, len)) {
				++num_matches;
				if ( num_matches == 1 && command) {
					*command = c;
				}
			}
		}
	}

	return num_matches;

}