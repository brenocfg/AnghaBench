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
struct hists_evsel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hists_evsel__exit ; 
 int /*<<< orphan*/  hists_evsel__init ; 
 int perf_evsel__object_config (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

int hists__init(void)
{
	int err = perf_evsel__object_config(sizeof(struct hists_evsel),
					    hists_evsel__init,
					    hists_evsel__exit);
	if (err)
		fputs("FATAL ERROR: Couldn't setup hists class\n", stderr);

	return err;
}