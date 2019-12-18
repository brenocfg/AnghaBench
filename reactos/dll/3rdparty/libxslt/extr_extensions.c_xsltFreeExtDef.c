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
typedef  TYPE_1__* xsltExtDefPtr ;
struct TYPE_4__ {struct TYPE_4__* URI; struct TYPE_4__* prefix; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmlFree (TYPE_1__*) ; 

__attribute__((used)) static void
xsltFreeExtDef(xsltExtDefPtr extensiond)
{
    if (extensiond == NULL)
        return;
    if (extensiond->prefix != NULL)
        xmlFree(extensiond->prefix);
    if (extensiond->URI != NULL)
        xmlFree(extensiond->URI);
    xmlFree(extensiond);
}