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
typedef  int /*<<< orphan*/ * xsltTransformFunction ;
typedef  int /*<<< orphan*/  xsltPreComputeFunction ;
typedef  int /*<<< orphan*/ * xsltExtElementPtr ;
typedef  int /*<<< orphan*/  xmlChar ;

/* Variables and functions */
 int /*<<< orphan*/ * xmlHashCreate (int) ; 
 int /*<<< orphan*/  xmlHashUpdateEntry2 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlMutexLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlMutexUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xsltElementsHash ; 
 int /*<<< orphan*/  xsltExtMutex ; 
 int /*<<< orphan*/  xsltFreeExtElementEntry ; 
 int /*<<< orphan*/ * xsltNewExtElement (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
xsltRegisterExtModuleElement(const xmlChar * name, const xmlChar * URI,
                             xsltPreComputeFunction precomp,
                             xsltTransformFunction transform)
{
    int ret = 0;

    xsltExtElementPtr ext;

    if ((name == NULL) || (URI == NULL) || (transform == NULL))
        return (-1);

    if (xsltElementsHash == NULL)
        xsltElementsHash = xmlHashCreate(10);
    if (xsltElementsHash == NULL)
        return (-1);

    xmlMutexLock(xsltExtMutex);

    ext = xsltNewExtElement(precomp, transform);
    if (ext == NULL) {
        ret = -1;
        goto done;
    }

    xmlHashUpdateEntry2(xsltElementsHash, name, URI, (void *) ext,
                        xsltFreeExtElementEntry);

done:
    xmlMutexUnlock(xsltExtMutex);

    return (ret);
}