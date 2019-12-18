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
struct TYPE_2__ {int /*<<< orphan*/  map; int /*<<< orphan*/  sym; } ;
struct hist_entry {TYPE_1__ ms; } ;
struct hist_browser_timer {int dummy; } ;
struct evsel {int dummy; } ;

/* Variables and functions */
 int symbol__gtk_annotate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct evsel*,struct hist_browser_timer*) ; 

int hist_entry__gtk_annotate(struct hist_entry *he,
			     struct evsel *evsel,
			     struct hist_browser_timer *hbt)
{
	return symbol__gtk_annotate(he->ms.sym, he->ms.map, evsel, hbt);
}