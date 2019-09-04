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
typedef  int /*<<< orphan*/  xsltStyleExtShutdownFunction ;
typedef  int /*<<< orphan*/  xsltStyleExtInitFunction ;
typedef  scalar_t__ xsltExtShutdownFunction ;
typedef  TYPE_1__* xsltExtModulePtr ;
typedef  int /*<<< orphan*/ * xsltExtInitFunction ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_4__ {scalar_t__ shutdownFunc; int /*<<< orphan*/ * initFunc; } ;

/* Variables and functions */
 int xmlHashAddEntry (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,void*) ; 
 int /*<<< orphan*/ * xmlHashCreate (int) ; 
 TYPE_1__* xmlHashLookup (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xmlMutexLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlMutexUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsltExtMutex ; 
 int /*<<< orphan*/ * xsltExtensionsHash ; 
 TYPE_1__* xsltNewExtModule (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
xsltRegisterExtModuleFull(const xmlChar * URI,
                          xsltExtInitFunction initFunc,
                          xsltExtShutdownFunction shutdownFunc,
                          xsltStyleExtInitFunction styleInitFunc,
                          xsltStyleExtShutdownFunction styleShutdownFunc)
{
    int ret;
    xsltExtModulePtr module;

    if ((URI == NULL) || (initFunc == NULL))
        return (-1);
    if (xsltExtensionsHash == NULL)
        xsltExtensionsHash = xmlHashCreate(10);

    if (xsltExtensionsHash == NULL)
        return (-1);

    xmlMutexLock(xsltExtMutex);

    module = xmlHashLookup(xsltExtensionsHash, URI);
    if (module != NULL) {
        if ((module->initFunc == initFunc) &&
            (module->shutdownFunc == shutdownFunc))
            ret = 0;
        else
            ret = -1;
        goto done;
    }
    module = xsltNewExtModule(initFunc, shutdownFunc,
                              styleInitFunc, styleShutdownFunc);
    if (module == NULL) {
        ret = -1;
        goto done;
    }
    ret = xmlHashAddEntry(xsltExtensionsHash, URI, (void *) module);

done:
    xmlMutexUnlock(xsltExtMutex);
    return (ret);
}