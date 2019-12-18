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
struct model {char digit; char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 struct model* models ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void usage(const char *mess)
{
	const struct model *m;

	fprintf(stderr, "Error: %s\n", mess);
	fprintf(stderr, "Usage: motorola-bin -device|--strip infile outfile\n");
	fprintf(stderr, "Known devices: ");

	for (m = models; m->digit != '\0'; m++)
		fprintf(stderr, " %c - %s", m->digit, m->name);

	fprintf(stderr, "\n");
	exit(1);
}