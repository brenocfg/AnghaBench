#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltTransformContextPtr ;
typedef  void* xmlNodePtr ;
typedef  TYPE_2__* xmlDocPtr ;
struct TYPE_9__ {TYPE_2__* fragment; } ;
struct TYPE_8__ {int /*<<< orphan*/ * prev; void* next; int /*<<< orphan*/  psvi; } ;
struct TYPE_7__ {TYPE_2__* tmpRVT; int /*<<< orphan*/ * contextVariable; } ;

/* Variables and functions */
 int /*<<< orphan*/  XSLT_RVT_LOCAL ; 
 TYPE_5__* XSLT_TCTXT_VARIABLE (TYPE_1__*) ; 

int
xsltRegisterTmpRVT(xsltTransformContextPtr ctxt, xmlDocPtr RVT)
{
    if ((ctxt == NULL) || (RVT == NULL))
	return(-1);

    RVT->prev = NULL;
    RVT->psvi = XSLT_RVT_LOCAL;

    /*
    * We'll restrict the lifetime of user-created fragments
    * insinde an xsl:variable and xsl:param to the lifetime of the
    * var/param itself.
    */
    if (ctxt->contextVariable != NULL) {
	RVT->next = (xmlNodePtr) XSLT_TCTXT_VARIABLE(ctxt)->fragment;
	XSLT_TCTXT_VARIABLE(ctxt)->fragment = RVT;
	return(0);
    }

    RVT->next = (xmlNodePtr) ctxt->tmpRVT;
    if (ctxt->tmpRVT != NULL)
	ctxt->tmpRVT->prev = (xmlNodePtr) RVT;
    ctxt->tmpRVT = RVT;
    return(0);
}