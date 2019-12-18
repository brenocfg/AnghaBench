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
struct symbol {int dummy; } ;
struct evsel {int dummy; } ;
struct annotation {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  annotation__calc_percent (struct annotation*,struct evsel*,int /*<<< orphan*/ ) ; 
 struct annotation* symbol__annotation (struct symbol*) ; 
 int /*<<< orphan*/  symbol__size (struct symbol*) ; 

void symbol__calc_percent(struct symbol *sym, struct evsel *evsel)
{
	struct annotation *notes = symbol__annotation(sym);

	annotation__calc_percent(notes, evsel, symbol__size(sym));
}