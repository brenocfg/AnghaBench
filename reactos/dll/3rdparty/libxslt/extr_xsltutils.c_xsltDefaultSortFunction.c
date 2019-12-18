#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltTransformContextPtr ;
typedef  TYPE_2__* xsltStylePreCompPtr ;
typedef  int /*<<< orphan*/  xsltStyleItemSortPtr ;
typedef  int /*<<< orphan*/  xsltLocaleChar ;
typedef  scalar_t__ xsltLocale ;
typedef  TYPE_3__* xmlXPathObjectPtr ;
typedef  TYPE_4__* xmlNodeSetPtr ;
typedef  TYPE_5__* xmlNodePtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_21__ {TYPE_2__* psvi; } ;
struct TYPE_20__ {int nodeNr; TYPE_5__** nodeTab; } ;
struct TYPE_19__ {scalar_t__ floatval; scalar_t__ index; scalar_t__ stringval; } ;
struct TYPE_18__ {scalar_t__ has_stype; int number; scalar_t__ has_order; int descending; scalar_t__ locale; int /*<<< orphan*/ * order; int /*<<< orphan*/ * stype; } ;
struct TYPE_17__ {TYPE_4__* nodeList; } ;

/* Variables and functions */
 int XSLT_MAX_SORT ; 
 int /*<<< orphan*/  XSLT_NAMESPACE ; 
 int /*<<< orphan*/  xmlFree (TYPE_3__**) ; 
 scalar_t__ xmlStrEqual (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int xmlStrcmp (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  xmlXPathFreeObject (TYPE_3__*) ; 
 scalar_t__ xmlXPathIsNaN (scalar_t__) ; 
 TYPE_3__** xsltComputeSortResult (TYPE_1__*,TYPE_5__*) ; 
 void* xsltEvalAttrValueTemplate (TYPE_1__*,TYPE_5__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int xsltLocaleStrcmp (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsltTransformError (TYPE_1__*,int /*<<< orphan*/ *,TYPE_5__*,char*,int /*<<< orphan*/ *) ; 

void
xsltDefaultSortFunction(xsltTransformContextPtr ctxt, xmlNodePtr *sorts,
	           int nbsorts) {
#ifdef XSLT_REFACTORED
    xsltStyleItemSortPtr comp;
#else
    xsltStylePreCompPtr comp;
#endif
    xmlXPathObjectPtr *resultsTab[XSLT_MAX_SORT];
    xmlXPathObjectPtr *results = NULL, *res;
    xmlNodeSetPtr list = NULL;
    int descending, number, desc, numb;
    int len = 0;
    int i, j, incr;
    int tst;
    int depth;
    xmlNodePtr node;
    xmlXPathObjectPtr tmp;
    int tempstype[XSLT_MAX_SORT], temporder[XSLT_MAX_SORT];

    if ((ctxt == NULL) || (sorts == NULL) || (nbsorts <= 0) ||
	(nbsorts >= XSLT_MAX_SORT))
	return;
    if (sorts[0] == NULL)
	return;
    comp = sorts[0]->psvi;
    if (comp == NULL)
	return;

    list = ctxt->nodeList;
    if ((list == NULL) || (list->nodeNr <= 1))
	return; /* nothing to do */

    for (j = 0; j < nbsorts; j++) {
	comp = sorts[j]->psvi;
	tempstype[j] = 0;
	if ((comp->stype == NULL) && (comp->has_stype != 0)) {
	    comp->stype =
		xsltEvalAttrValueTemplate(ctxt, sorts[j],
					  (const xmlChar *) "data-type",
					  XSLT_NAMESPACE);
	    if (comp->stype != NULL) {
		tempstype[j] = 1;
		if (xmlStrEqual(comp->stype, (const xmlChar *) "text"))
		    comp->number = 0;
		else if (xmlStrEqual(comp->stype, (const xmlChar *) "number"))
		    comp->number = 1;
		else {
		    xsltTransformError(ctxt, NULL, sorts[j],
			  "xsltDoSortFunction: no support for data-type = %s\n",
				     comp->stype);
		    comp->number = 0; /* use default */
		}
	    }
	}
	temporder[j] = 0;
	if ((comp->order == NULL) && (comp->has_order != 0)) {
	    comp->order = xsltEvalAttrValueTemplate(ctxt, sorts[j],
						    (const xmlChar *) "order",
						    XSLT_NAMESPACE);
	    if (comp->order != NULL) {
		temporder[j] = 1;
		if (xmlStrEqual(comp->order, (const xmlChar *) "ascending"))
		    comp->descending = 0;
		else if (xmlStrEqual(comp->order,
				     (const xmlChar *) "descending"))
		    comp->descending = 1;
		else {
		    xsltTransformError(ctxt, NULL, sorts[j],
			     "xsltDoSortFunction: invalid value %s for order\n",
				     comp->order);
		    comp->descending = 0; /* use default */
		}
	    }
	}
    }

    len = list->nodeNr;

    resultsTab[0] = xsltComputeSortResult(ctxt, sorts[0]);
    for (i = 1;i < XSLT_MAX_SORT;i++)
	resultsTab[i] = NULL;

    results = resultsTab[0];

    comp = sorts[0]->psvi;
    descending = comp->descending;
    number = comp->number;
    if (results == NULL)
	return;

    /* Shell's sort of node-set */
    for (incr = len / 2; incr > 0; incr /= 2) {
	for (i = incr; i < len; i++) {
	    j = i - incr;
	    if (results[i] == NULL)
		continue;

	    while (j >= 0) {
		if (results[j] == NULL)
		    tst = 1;
		else {
		    if (number) {
			/* We make NaN smaller than number in accordance
			   with XSLT spec */
			if (xmlXPathIsNaN(results[j]->floatval)) {
			    if (xmlXPathIsNaN(results[j + incr]->floatval))
				tst = 0;
			    else
				tst = -1;
			} else if (xmlXPathIsNaN(results[j + incr]->floatval))
			    tst = 1;
			else if (results[j]->floatval ==
				results[j + incr]->floatval)
			    tst = 0;
			else if (results[j]->floatval >
				results[j + incr]->floatval)
			    tst = 1;
			else tst = -1;
		    } else if(comp->locale != (xsltLocale)0) {
			tst = xsltLocaleStrcmp(
			    comp->locale,
			    (xsltLocaleChar *) results[j]->stringval,
			    (xsltLocaleChar *) results[j + incr]->stringval);
		    } else {
			tst = xmlStrcmp(results[j]->stringval,
				     results[j + incr]->stringval);
		    }
		    if (descending)
			tst = -tst;
		}
		if (tst == 0) {
		    /*
		     * Okay we need to use multi level sorts
		     */
		    depth = 1;
		    while (depth < nbsorts) {
			if (sorts[depth] == NULL)
			    break;
			comp = sorts[depth]->psvi;
			if (comp == NULL)
			    break;
			desc = comp->descending;
			numb = comp->number;

			/*
			 * Compute the result of the next level for the
			 * full set, this might be optimized ... or not
			 */
			if (resultsTab[depth] == NULL)
			    resultsTab[depth] = xsltComputeSortResult(ctxt,
				                        sorts[depth]);
			res = resultsTab[depth];
			if (res == NULL)
			    break;
			if (res[j] == NULL) {
			    if (res[j+incr] != NULL)
				tst = 1;
			} else if (res[j+incr] == NULL) {
			    tst = -1;
			} else {
			    if (numb) {
				/* We make NaN smaller than number in
				   accordance with XSLT spec */
				if (xmlXPathIsNaN(res[j]->floatval)) {
				    if (xmlXPathIsNaN(res[j +
						incr]->floatval))
					tst = 0;
				    else
				        tst = -1;
				} else if (xmlXPathIsNaN(res[j + incr]->
						floatval))
				    tst = 1;
				else if (res[j]->floatval == res[j + incr]->
						floatval)
				    tst = 0;
				else if (res[j]->floatval >
					res[j + incr]->floatval)
				    tst = 1;
				else tst = -1;
			    } else if(comp->locale != (xsltLocale)0) {
				tst = xsltLocaleStrcmp(
				    comp->locale,
				    (xsltLocaleChar *) res[j]->stringval,
				    (xsltLocaleChar *) res[j + incr]->stringval);
			    } else {
				tst = xmlStrcmp(res[j]->stringval,
					     res[j + incr]->stringval);
			    }
			    if (desc)
				tst = -tst;
			}

			/*
			 * if we still can't differenciate at this level
			 * try one level deeper.
			 */
			if (tst != 0)
			    break;
			depth++;
		    }
		}
		if (tst == 0) {
		    tst = results[j]->index > results[j + incr]->index;
		}
		if (tst > 0) {
		    tmp = results[j];
		    results[j] = results[j + incr];
		    results[j + incr] = tmp;
		    node = list->nodeTab[j];
		    list->nodeTab[j] = list->nodeTab[j + incr];
		    list->nodeTab[j + incr] = node;
		    depth = 1;
		    while (depth < nbsorts) {
			if (sorts[depth] == NULL)
			    break;
			if (resultsTab[depth] == NULL)
			    break;
			res = resultsTab[depth];
			tmp = res[j];
			res[j] = res[j + incr];
			res[j + incr] = tmp;
			depth++;
		    }
		    j -= incr;
		} else
		    break;
	    }
	}
    }

    for (j = 0; j < nbsorts; j++) {
	comp = sorts[j]->psvi;
	if (tempstype[j] == 1) {
	    /* The data-type needs to be recomputed each time */
	    xmlFree((void *)(comp->stype));
	    comp->stype = NULL;
	}
	if (temporder[j] == 1) {
	    /* The order needs to be recomputed each time */
	    xmlFree((void *)(comp->order));
	    comp->order = NULL;
	}
	if (resultsTab[j] != NULL) {
	    for (i = 0;i < len;i++)
		xmlXPathFreeObject(resultsTab[j][i]);
	    xmlFree(resultsTab[j]);
	}
    }
}