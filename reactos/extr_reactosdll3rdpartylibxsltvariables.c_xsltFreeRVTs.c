#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltTransformContextPtr ;
typedef  TYPE_2__* xmlDocPtr ;
struct TYPE_6__ {int /*<<< orphan*/ * _private; scalar_t__ next; } ;
struct TYPE_5__ {TYPE_2__* persistRVT; TYPE_2__* tmpRVT; TYPE_2__* localRVT; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmlFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFreeDoc (TYPE_2__*) ; 
 int /*<<< orphan*/  xsltFreeDocumentKeys (int /*<<< orphan*/ *) ; 

void
xsltFreeRVTs(xsltTransformContextPtr ctxt)
{
    xmlDocPtr cur, next;

    if (ctxt == NULL)
	return;
    /*
    * Local fragments.
    */
    cur = ctxt->localRVT;
    while (cur != NULL) {
        next = (xmlDocPtr) cur->next;
	if (cur->_private != NULL) {
	    xsltFreeDocumentKeys(cur->_private);
	    xmlFree(cur->_private);
	}
	xmlFreeDoc(cur);
	cur = next;
    }
    ctxt->localRVT = NULL;
    /*
    * User-created per-template fragments.
    */
    cur = ctxt->tmpRVT;
    while (cur != NULL) {
        next = (xmlDocPtr) cur->next;
	if (cur->_private != NULL) {
	    xsltFreeDocumentKeys(cur->_private);
	    xmlFree(cur->_private);
	}
	xmlFreeDoc(cur);
	cur = next;
    }
    ctxt->tmpRVT = NULL;
    /*
    * Global fragments.
    */
    cur = ctxt->persistRVT;
    while (cur != NULL) {
        next = (xmlDocPtr) cur->next;
	if (cur->_private != NULL) {
	    xsltFreeDocumentKeys(cur->_private);
	    xmlFree(cur->_private);
	}
	xmlFreeDoc(cur);
	cur = next;
    }
    ctxt->persistRVT = NULL;
}