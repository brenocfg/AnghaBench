#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* xsltTransformContextPtr ;
typedef  TYPE_3__* xsltStackElemPtr ;
typedef  int /*<<< orphan*/  xsltStackElem ;
struct TYPE_9__ {TYPE_2__* context; struct TYPE_9__* next; } ;
struct TYPE_8__ {TYPE_1__* cache; } ;
struct TYPE_7__ {int /*<<< orphan*/  dbgReusedVars; int /*<<< orphan*/  nbStackItems; TYPE_3__* stackItems; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xmlMalloc (int) ; 
 int /*<<< orphan*/  xsltTransformError (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static xsltStackElemPtr
xsltNewStackElem(xsltTransformContextPtr ctxt)
{
    xsltStackElemPtr ret;
    /*
    * Reuse a stack item from the cache if available.
    */
    if (ctxt && ctxt->cache->stackItems) {
	ret = ctxt->cache->stackItems;
	ctxt->cache->stackItems = ret->next;
	ret->next = NULL;
	ctxt->cache->nbStackItems--;
#ifdef XSLT_DEBUG_PROFILE_CACHE
	ctxt->cache->dbgReusedVars++;
#endif
	return(ret);
    }
    ret = (xsltStackElemPtr) xmlMalloc(sizeof(xsltStackElem));
    if (ret == NULL) {
	xsltTransformError(NULL, NULL, NULL,
		"xsltNewStackElem : malloc failed\n");
	return(NULL);
    }
    memset(ret, 0, sizeof(xsltStackElem));
    ret->context = ctxt;
    return(ret);
}