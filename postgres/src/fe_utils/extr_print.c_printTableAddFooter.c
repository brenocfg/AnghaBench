#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* next; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ printTableFooter ;
struct TYPE_6__ {TYPE_1__* footer; TYPE_1__* footers; } ;
typedef  TYPE_2__ printTableContent ;

/* Variables and functions */
 TYPE_1__* pg_malloc0 (int) ; 
 int /*<<< orphan*/  pg_strdup (char const*) ; 

void
printTableAddFooter(printTableContent *const content, const char *footer)
{
	printTableFooter *f;

	f = pg_malloc0(sizeof(*f));
	f->data = pg_strdup(footer);

	if (content->footers == NULL)
		content->footers = f;
	else
		content->footer->next = f;

	content->footer = f;
}