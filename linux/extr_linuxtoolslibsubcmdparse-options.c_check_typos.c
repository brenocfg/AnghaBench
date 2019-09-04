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
struct option {scalar_t__ type; char const* long_name; } ;

/* Variables and functions */
 scalar_t__ OPTION_END ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char const*) ; 
 scalar_t__ strstarts (char const*,char const*) ; 

__attribute__((used)) static void check_typos(const char *arg, const struct option *options)
{
	if (strlen(arg) < 3)
		return;

	if (strstarts(arg, "no-")) {
		fprintf(stderr, " Error: did you mean `--%s` (with two dashes ?)\n", arg);
		exit(129);
	}

	for (; options->type != OPTION_END; options++) {
		if (!options->long_name)
			continue;
		if (strstarts(options->long_name, arg)) {
			fprintf(stderr, " Error: did you mean `--%s` (with two dashes ?)\n", arg);
			exit(129);
		}
	}
}