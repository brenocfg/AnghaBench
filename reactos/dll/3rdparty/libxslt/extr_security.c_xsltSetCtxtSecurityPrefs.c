#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltTransformContextPtr ;
typedef  scalar_t__ xsltSecurityPrefsPtr ;
struct TYPE_3__ {void* sec; } ;

/* Variables and functions */

int
xsltSetCtxtSecurityPrefs(xsltSecurityPrefsPtr sec,
	                 xsltTransformContextPtr ctxt) {
    if (ctxt == NULL)
	return(-1);
    ctxt->sec = (void *) sec;
    return(0);
}