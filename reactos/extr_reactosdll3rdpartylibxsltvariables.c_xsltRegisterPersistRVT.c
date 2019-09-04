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
typedef  void* xmlNodePtr ;
typedef  TYPE_2__* xmlDocPtr ;
struct TYPE_6__ {int /*<<< orphan*/ * prev; void* next; int /*<<< orphan*/  psvi; } ;
struct TYPE_5__ {TYPE_2__* persistRVT; } ;

/* Variables and functions */
 int /*<<< orphan*/  XSLT_RVT_GLOBAL ; 

int
xsltRegisterPersistRVT(xsltTransformContextPtr ctxt, xmlDocPtr RVT)
{
    if ((ctxt == NULL) || (RVT == NULL)) return(-1);

    RVT->psvi = XSLT_RVT_GLOBAL;
    RVT->prev = NULL;
    RVT->next = (xmlNodePtr) ctxt->persistRVT;
    if (ctxt->persistRVT != NULL)
	ctxt->persistRVT->prev = (xmlNodePtr) RVT;
    ctxt->persistRVT = RVT;
    return(0);
}