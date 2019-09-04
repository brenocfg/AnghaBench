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
struct symbol {int dummy; } ;
struct TYPE_2__ {struct symbol* sym; } ;
struct hist_entry {TYPE_1__ ms; } ;

/* Variables and functions */
 int /*<<< orphan*/  symbol__annotate_zero_histograms (struct symbol*) ; 

__attribute__((used)) static void __zero_source_counters(struct hist_entry *he)
{
	struct symbol *sym = he->ms.sym;
	symbol__annotate_zero_histograms(sym);
}