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
typedef  int /*<<< orphan*/ * xmlXPathFunction ;
typedef  int /*<<< orphan*/  xmlChar ;

/* Variables and functions */
 int /*<<< orphan*/  XML_CAST_FPTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xmlHashCreate (int) ; 
 int /*<<< orphan*/  xmlHashUpdateEntry2 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlMutexLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlMutexUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsltExtMutex ; 
 int /*<<< orphan*/ * xsltFunctionsHash ; 

int
xsltRegisterExtModuleFunction(const xmlChar * name, const xmlChar * URI,
                              xmlXPathFunction function)
{
    if ((name == NULL) || (URI == NULL) || (function == NULL))
        return (-1);

    if (xsltFunctionsHash == NULL)
        xsltFunctionsHash = xmlHashCreate(10);
    if (xsltFunctionsHash == NULL)
        return (-1);

    xmlMutexLock(xsltExtMutex);

    xmlHashUpdateEntry2(xsltFunctionsHash, name, URI,
                        XML_CAST_FPTR(function), NULL);

    xmlMutexUnlock(xsltExtMutex);

    return (0);
}