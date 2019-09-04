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

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,int,char const*) ; 
 int /*<<< orphan*/  printf (char*,char const*,int,char const*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void inline __mpx_dig_abort(const char *file, const char *func, int line)
{
	fprintf(stderr, "MPX dig abort @ %s::%d in %s()\n", file, line, func);
	printf("MPX dig abort @ %s::%d in %s()\n", file, line, func);
	abort();
}