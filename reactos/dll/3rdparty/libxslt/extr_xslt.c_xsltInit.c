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

/* Variables and functions */
 int initialized ; 
 int /*<<< orphan*/  xmlNewRMutex () ; 
 int /*<<< orphan*/  xsltLocaleMutex ; 
 int /*<<< orphan*/  xsltRegisterAllExtras () ; 

void
xsltInit (void) {
    if (initialized == 0) {
	initialized = 1;
#ifdef XSLT_LOCALE_WINAPI
	xsltLocaleMutex = xmlNewRMutex();
#endif
        xsltRegisterAllExtras();
    }
}