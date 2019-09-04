#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hists {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  use_callchain; } ;

/* Variables and functions */
 int /*<<< orphan*/  hists__baseline_only (struct hists*) ; 
 int /*<<< orphan*/  hists__fprintf (struct hists*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hists__output_resort (struct hists*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hists__precompute (struct hists*) ; 
 int /*<<< orphan*/  quiet ; 
 scalar_t__ show_baseline_only ; 
 int /*<<< orphan*/  stdout ; 
 TYPE_1__ symbol_conf ; 

__attribute__((used)) static void hists__process(struct hists *hists)
{
	if (show_baseline_only)
		hists__baseline_only(hists);

	hists__precompute(hists);
	hists__output_resort(hists, NULL);

	hists__fprintf(hists, !quiet, 0, 0, 0, stdout,
		       !symbol_conf.use_callchain);
}