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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,size_t,size_t,char const*) ; 
 int getpid () ; 
 int /*<<< orphan*/  setlinebuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static void zend_jit_perf_map_register(const char *name, void *start, size_t size)
{
	static FILE *fp = NULL;

	if (!fp) {
		char filename[64];

		sprintf(filename, "/tmp/perf-%d.map", getpid());
		fp = fopen(filename, "w");
		if (!fp) {
			return;
		}
	    setlinebuf(fp);
	}
	fprintf(fp, "%zx %zx %s\n", (size_t)(uintptr_t)start, size, name);
}