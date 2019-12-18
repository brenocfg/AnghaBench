#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltStylesheetPtr ;
typedef  TYPE_2__* xsltExtModulePtr ;
typedef  int /*<<< orphan*/ * xsltExtDataPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_10__ {int /*<<< orphan*/  (* styleShutdownFunc ) (TYPE_1__*,int /*<<< orphan*/  const*,void*) ;void* (* styleInitFunc ) (TYPE_1__*,int /*<<< orphan*/  const*) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  errors; int /*<<< orphan*/ * extInfos; } ;

/* Variables and functions */
 void* stub1 (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/  const*,void*) ; 
 scalar_t__ xmlHashAddEntry (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,void*) ; 
 int /*<<< orphan*/ * xmlHashCreate (int) ; 
 TYPE_2__* xmlHashLookup (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xmlMutexLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlMutexUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsltExtMutex ; 
 int /*<<< orphan*/ * xsltExtensionsHash ; 
 int /*<<< orphan*/  xsltFreeExtData (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsltGenericDebug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xsltGenericDebugContext ; 
 int /*<<< orphan*/ * xsltNewExtData (TYPE_2__*,void*) ; 
 int /*<<< orphan*/  xsltTransformError (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static xsltExtDataPtr
xsltStyleInitializeStylesheetModule(xsltStylesheetPtr style,
				     const xmlChar * URI)
{
    xsltExtDataPtr dataContainer;
    void *userData = NULL;
    xsltExtModulePtr module;

    if ((style == NULL) || (URI == NULL))
	return(NULL);

    if (xsltExtensionsHash == NULL) {
#ifdef WITH_XSLT_DEBUG_EXTENSIONS
	xsltGenericDebug(xsltGenericDebugContext,
	    "Not registered extension module: %s\n", URI);
#endif
	return(NULL);
    }

    xmlMutexLock(xsltExtMutex);

    module = xmlHashLookup(xsltExtensionsHash, URI);

    xmlMutexUnlock(xsltExtMutex);

    if (module == NULL) {
#ifdef WITH_XSLT_DEBUG_EXTENSIONS
	xsltGenericDebug(xsltGenericDebugContext,
	    "Not registered extension module: %s\n", URI);
#endif
	return (NULL);
    }
    /*
    * The specified module was registered so initialize it.
    */
    if (style->extInfos == NULL) {
	style->extInfos = xmlHashCreate(10);
	if (style->extInfos == NULL)
	    return (NULL);
    }
    /*
    * Fire the initialization callback if available.
    */
    if (module->styleInitFunc == NULL) {
#ifdef WITH_XSLT_DEBUG_EXTENSIONS
	xsltGenericDebug(xsltGenericDebugContext,
	    "Initializing module with *no* callback: %s\n", URI);
#endif
    } else {
#ifdef WITH_XSLT_DEBUG_EXTENSIONS
	xsltGenericDebug(xsltGenericDebugContext,
	    "Initializing module with callback: %s\n", URI);
#endif
	/*
	* Fire the initialization callback.
	*/
	userData = module->styleInitFunc(style, URI);
    }
    /*
    * Store the user-data in the context of the given stylesheet.
    */
    dataContainer = xsltNewExtData(module, userData);
    if (dataContainer == NULL)
	return (NULL);

    if (xmlHashAddEntry(style->extInfos, URI,
	(void *) dataContainer) < 0)
    {
	xsltTransformError(NULL, style, NULL,
	    "Failed to register module '%s'.\n", URI);
	style->errors++;
	if (module->styleShutdownFunc)
	    module->styleShutdownFunc(style, URI, userData);
	xsltFreeExtData(dataContainer);
	return (NULL);
    }

    return(dataContainer);
}