#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltTransformCachePtr ;
typedef  TYPE_1__* xsltStackElemPtr ;
typedef  int /*<<< orphan*/  xsltDocumentPtr ;
typedef  TYPE_3__* xmlDocPtr ;
struct TYPE_8__ {TYPE_1__* _private; scalar_t__ next; } ;
struct TYPE_7__ {struct TYPE_7__* next; struct TYPE_7__* stackItems; TYPE_3__* RVT; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmlFree (TYPE_1__*) ; 
 int /*<<< orphan*/  xmlFreeDoc (TYPE_3__*) ; 
 int /*<<< orphan*/  xsltFreeDocumentKeys (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xsltTransformCacheFree(xsltTransformCachePtr cache)
{
    if (cache == NULL)
	return;
    /*
    * Free tree fragments.
    */
    if (cache->RVT) {
	xmlDocPtr tmp, cur = cache->RVT;
	while (cur) {
	    tmp = cur;
	    cur = (xmlDocPtr) cur->next;
	    if (tmp->_private != NULL) {
		/*
		* Tree the document info.
		*/
		xsltFreeDocumentKeys((xsltDocumentPtr) tmp->_private);
		xmlFree(tmp->_private);
	    }
	    xmlFreeDoc(tmp);
	}
    }
    /*
    * Free vars/params.
    */
    if (cache->stackItems) {
	xsltStackElemPtr tmp, cur = cache->stackItems;
	while (cur) {
	    tmp = cur;
	    cur = cur->next;
	    /*
	    * REVISIT TODO: Should be call a destruction-function
	    * instead?
	    */
	    xmlFree(tmp);
	}
    }
    xmlFree(cache);
}