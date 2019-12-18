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
struct TYPE_6__ {TYPE_1__* footer; int /*<<< orphan*/ * footers; } ;
typedef  TYPE_2__ printTableContent ;
struct TYPE_5__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_strdup (char const*) ; 
 int /*<<< orphan*/  printTableAddFooter (TYPE_2__* const,char const*) ; 

void
printTableSetFooter(printTableContent *const content, const char *footer)
{
	if (content->footers != NULL)
	{
		free(content->footer->data);
		content->footer->data = pg_strdup(footer);
	}
	else
		printTableAddFooter(content, footer);
}