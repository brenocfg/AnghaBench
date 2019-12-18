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
struct ui_progress {int dummy; } ;
struct hists {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  use_callchain; } ;

/* Variables and functions */
 int /*<<< orphan*/  output_resort (struct hists*,struct ui_progress*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__ symbol_conf ; 

void hists__output_resort(struct hists *hists, struct ui_progress *prog)
{
	output_resort(hists, prog, symbol_conf.use_callchain, NULL, NULL);
}