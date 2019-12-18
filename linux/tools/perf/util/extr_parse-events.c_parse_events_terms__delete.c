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
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct list_head*) ; 
 int /*<<< orphan*/  parse_events_terms__purge (struct list_head*) ; 

void parse_events_terms__delete(struct list_head *terms)
{
	if (!terms)
		return;
	parse_events_terms__purge(terms);
	free(terms);
}