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
typedef  int /*<<< orphan*/  procfile ;

/* Variables and functions */
 int /*<<< orphan*/  PROCFILE_FLAG_NO_ERROR_ON_FILE_IO ; 
 int /*<<< orphan*/  begin_tsc () ; 
 unsigned long end_tsc () ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * procfile_readall1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * procfile_reopen (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

unsigned long test_method1(void) {
	static procfile *ff = NULL;

	ff = procfile_reopen(ff, "/proc/self/status", " \t:,-()/", PROCFILE_FLAG_NO_ERROR_ON_FILE_IO);
	if(!ff) {
		fprintf(stderr, "Failed to open filename\n");
		exit(1);
	}

	begin_tsc();
	ff = procfile_readall1(ff);
	unsigned long c = end_tsc();

	if(!ff) {
		fprintf(stderr, "Failed to read filename\n");
		exit(1);
	}

	return c;
}