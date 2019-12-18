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
 int /*<<< orphan*/  xmlFreeMutex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlHashFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlHashScan (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlMutexLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlMutexUnlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xsltExtMutex ; 
 int /*<<< orphan*/  xsltFreeLocales () ; 
 int /*<<< orphan*/  xsltHashScannerModuleFree ; 
 int /*<<< orphan*/ * xsltModuleHash ; 
 int /*<<< orphan*/  xsltUninit () ; 
 int /*<<< orphan*/  xsltUnregisterAllExtModuleElement () ; 
 int /*<<< orphan*/  xsltUnregisterAllExtModuleFunction () ; 
 int /*<<< orphan*/  xsltUnregisterAllExtModuleTopLevel () ; 
 int /*<<< orphan*/  xsltUnregisterAllExtModules () ; 

void
xsltCleanupGlobals(void)
{
    xsltUnregisterAllExtModules();
    xsltUnregisterAllExtModuleFunction();
    xsltUnregisterAllExtModuleElement();
    xsltUnregisterAllExtModuleTopLevel();

    xmlMutexLock(xsltExtMutex);
    /* cleanup dynamic module hash */
    if (NULL != xsltModuleHash) {
        xmlHashScan(xsltModuleHash, xsltHashScannerModuleFree, 0);
        xmlHashFree(xsltModuleHash, NULL);
        xsltModuleHash = NULL;
    }
    xmlMutexUnlock(xsltExtMutex);

    xmlFreeMutex(xsltExtMutex);
    xsltExtMutex = NULL;
    xsltFreeLocales();
    xsltUninit();
}