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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/  xmlHashScanFull (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlMutexLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlMutexUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsltDebugDumpExtModulesCallback ; 
 int /*<<< orphan*/  xsltDebugDumpExtensionsCallback ; 
 int /*<<< orphan*/  xsltElementsHash ; 
 int /*<<< orphan*/  xsltExtMutex ; 
 int /*<<< orphan*/  xsltExtensionsHash ; 
 int /*<<< orphan*/  xsltFunctionsHash ; 

void
xsltDebugDumpExtensions(FILE * output)
{
    if (output == NULL)
        output = stdout;
    fprintf(output,
            "Registered XSLT Extensions\n--------------------------\n");
    if (!xsltFunctionsHash)
        fprintf(output, "No registered extension functions\n");
    else {
        fprintf(output, "Registered Extension Functions:\n");
        xmlMutexLock(xsltExtMutex);
        xmlHashScanFull(xsltFunctionsHash, xsltDebugDumpExtensionsCallback,
                        output);
        xmlMutexUnlock(xsltExtMutex);
    }
    if (!xsltElementsHash)
        fprintf(output, "\nNo registered extension elements\n");
    else {
        fprintf(output, "\nRegistered Extension Elements:\n");
        xmlMutexLock(xsltExtMutex);
        xmlHashScanFull(xsltElementsHash, xsltDebugDumpExtensionsCallback,
                        output);
        xmlMutexUnlock(xsltExtMutex);
    }
    if (!xsltExtensionsHash)
        fprintf(output, "\nNo registered extension modules\n");
    else {
        fprintf(output, "\nRegistered Extension Modules:\n");
        xmlMutexLock(xsltExtMutex);
        xmlHashScanFull(xsltExtensionsHash, xsltDebugDumpExtModulesCallback,
                        output);
        xmlMutexUnlock(xsltExtMutex);
    }

}