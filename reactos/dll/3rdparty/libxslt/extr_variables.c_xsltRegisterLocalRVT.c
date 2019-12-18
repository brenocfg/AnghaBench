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
struct TYPE_9__ {int flags; TYPE_2__* fragment; } ;
struct TYPE_8__ {int /*<<< orphan*/ * prev; void* next; int /*<<< orphan*/  psvi; } ;
struct TYPE_7__ {TYPE_2__* localRVT; int /*<<< orphan*/ * contextVariable; } ;

/* Variables and functions */
 int /*<<< orphan*/  XSLT_RVT_LOCAL ; 
 TYPE_5__* XSLT_TCTXT_VARIABLE (TYPE_1__*) ; 
 int XSLT_VAR_IN_SELECT ; 

int
xsltRegisterLocalRVT(xsltTransformContextPtr ctxt,
		     xmlDocPtr RVT)
{
    if ((ctxt == NULL) || (RVT == NULL))
	return(-1);

    RVT->prev = NULL;
    RVT->psvi = XSLT_RVT_LOCAL;

    /*
    * When evaluating "select" expressions of xsl:variable
    * and xsl:param, we need to bind newly created tree fragments
    * to the variable itself; otherwise the fragment will be
    * freed before we leave the scope of a var.
    */
    if ((ctxt->contextVariable != NULL) &&
	(XSLT_TCTXT_VARIABLE(ctxt)->flags & XSLT_VAR_IN_SELECT))
    {
	RVT->next = (xmlNodePtr) XSLT_TCTXT_VARIABLE(ctxt)->fragment;
	XSLT_TCTXT_VARIABLE(ctxt)->fragment = RVT;
	return(0);
    }
    /*
    * Store the fragment in the scope of the current instruction.
    * If not reference by a returning instruction (like EXSLT's function),
    * then this fragment will be freed, when the instruction exits.
    */
    RVT->next = (xmlNodePtr) ctxt->localRVT;
    if (ctxt->localRVT != NULL)
	ctxt->localRVT->prev = (xmlNodePtr) RVT;
    ctxt->localRVT = RVT;
    return(0);
}