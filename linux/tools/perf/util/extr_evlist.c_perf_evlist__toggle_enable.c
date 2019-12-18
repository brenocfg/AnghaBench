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
struct evlist {scalar_t__ enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  evlist__disable (struct evlist*) ; 
 int /*<<< orphan*/  evlist__enable (struct evlist*) ; 
 int /*<<< orphan*/  stub1 (struct evlist*) ; 

void perf_evlist__toggle_enable(struct evlist *evlist)
{
	(evlist->enabled ? evlist__disable : evlist__enable)(evlist);
}