#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltTemplatePtr ;
struct TYPE_4__ {struct TYPE_4__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  xsltFreeTemplate (TYPE_1__*) ; 

__attribute__((used)) static void
xsltFreeTemplateList(xsltTemplatePtr template) {
    xsltTemplatePtr cur;

    while (template != NULL) {
	cur = template;
	template = template->next;
	xsltFreeTemplate(cur);
    }
}