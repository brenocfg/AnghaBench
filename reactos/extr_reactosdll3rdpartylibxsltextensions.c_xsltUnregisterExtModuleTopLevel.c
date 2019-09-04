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
 int xmlHashRemoveEntry2 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlMutexLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlMutexUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsltExtMutex ; 
 int /*<<< orphan*/ * xsltTopLevelsHash ; 

int
xsltUnregisterExtModuleTopLevel(const xmlChar * name, const xmlChar * URI)
{
    int ret;

    if ((xsltTopLevelsHash == NULL) || (name == NULL) || (URI == NULL))
        return (-1);

    xmlMutexLock(xsltExtMutex);

    ret = xmlHashRemoveEntry2(xsltTopLevelsHash, name, URI, NULL);

    xmlMutexUnlock(xsltExtMutex);

    return(ret);
}