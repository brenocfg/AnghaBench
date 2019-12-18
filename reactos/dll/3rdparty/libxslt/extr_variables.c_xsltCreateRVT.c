#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* xsltTransformContextPtr ;
typedef  TYPE_3__* xmlDocPtr ;
struct TYPE_10__ {int /*<<< orphan*/ * parent; struct TYPE_10__* doc; int /*<<< orphan*/  dict; int /*<<< orphan*/ * prev; int /*<<< orphan*/ * next; } ;
struct TYPE_9__ {int /*<<< orphan*/  dict; TYPE_1__* cache; } ;
struct TYPE_8__ {scalar_t__ nbRVT; int /*<<< orphan*/  dbgReusedRVTs; TYPE_3__* RVT; } ;

/* Variables and functions */
 int /*<<< orphan*/  XSLT_MARK_RES_TREE_FRAG (TYPE_3__*) ; 
 int /*<<< orphan*/  xmlDictReference (int /*<<< orphan*/ ) ; 
 TYPE_3__* xmlNewDoc (int /*<<< orphan*/ *) ; 

xmlDocPtr
xsltCreateRVT(xsltTransformContextPtr ctxt)
{
    xmlDocPtr container;

    /*
    * Question: Why is this function public?
    * Answer: It is called by the EXSLT module.
    */
    if (ctxt == NULL)
	return(NULL);

    /*
    * Reuse a RTF from the cache if available.
    */
    if (ctxt->cache->RVT) {
	container = ctxt->cache->RVT;
	ctxt->cache->RVT = (xmlDocPtr) container->next;
	/* clear the internal pointers */
	container->next = NULL;
	container->prev = NULL;
	if (ctxt->cache->nbRVT > 0)
	    ctxt->cache->nbRVT--;
#ifdef XSLT_DEBUG_PROFILE_CACHE
	ctxt->cache->dbgReusedRVTs++;
#endif
	return(container);
    }

    container = xmlNewDoc(NULL);
    if (container == NULL)
	return(NULL);
    container->dict = ctxt->dict;
    xmlDictReference(container->dict);
    XSLT_MARK_RES_TREE_FRAG(container);
    container->doc = container;
    container->parent = NULL;
    return(container);
}