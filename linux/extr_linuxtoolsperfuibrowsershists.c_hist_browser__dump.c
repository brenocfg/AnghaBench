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
struct hist_browser {int print_seq; } ;
typedef  int /*<<< orphan*/  filename ;
typedef  int /*<<< orphan*/  bf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  F_OK ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  hist_browser__fprintf (struct hist_browser*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scnprintf (char*,int,char*,int) ; 
 char* str_error_r (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ui_helpline__fpush (char*,...) ; 

__attribute__((used)) static int hist_browser__dump(struct hist_browser *browser)
{
	char filename[64];
	FILE *fp;

	while (1) {
		scnprintf(filename, sizeof(filename), "perf.hist.%d", browser->print_seq);
		if (access(filename, F_OK))
			break;
		/*
 		 * XXX: Just an arbitrary lazy upper limit
 		 */
		if (++browser->print_seq == 8192) {
			ui_helpline__fpush("Too many perf.hist.N files, nothing written!");
			return -1;
		}
	}

	fp = fopen(filename, "w");
	if (fp == NULL) {
		char bf[64];
		const char *err = str_error_r(errno, bf, sizeof(bf));
		ui_helpline__fpush("Couldn't write to %s: %s", filename, err);
		return -1;
	}

	++browser->print_seq;
	hist_browser__fprintf(browser, fp);
	fclose(fp);
	ui_helpline__fpush("%s written!", filename);

	return 0;
}