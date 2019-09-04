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
typedef  int /*<<< orphan*/  xmlChar ;

/* Variables and functions */
 int xmlHashRemoveEntry (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlMutexLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlMutexUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsltExtMutex ; 
 int /*<<< orphan*/ * xsltExtensionsHash ; 
 int /*<<< orphan*/  xsltFreeExtModuleEntry ; 

int
xsltUnregisterExtModule(const xmlChar * URI)
{
    int ret;

    if (URI == NULL)
        return (-1);
    if (xsltExtensionsHash == NULL)
        return (-1);

    xmlMutexLock(xsltExtMutex);

    ret = xmlHashRemoveEntry(xsltExtensionsHash, URI, xsltFreeExtModuleEntry);

    xmlMutexUnlock(xsltExtMutex);

    return (ret);
}