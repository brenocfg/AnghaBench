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
typedef  int /*<<< orphan*/  xsltTemplatePtr ;
typedef  int /*<<< orphan*/  xmlNodePtr ;
struct TYPE_2__ {int (* add ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ xsltDebuggerCurrentCallbacks ; 

int
xslAddCall(xsltTemplatePtr templ, xmlNodePtr source)
{
    if (xsltDebuggerCurrentCallbacks.add != NULL)
	return(xsltDebuggerCurrentCallbacks.add(templ, source));
    return(0);
}