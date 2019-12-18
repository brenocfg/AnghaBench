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
typedef  TYPE_1__* xsltTransformContextPtr ;
typedef  TYPE_2__* xsltStylesheetPtr ;
typedef  TYPE_3__* xsltKeyDefPtr ;
struct TYPE_9__ {struct TYPE_9__* next; } ;
struct TYPE_8__ {TYPE_3__* keys; int /*<<< orphan*/ * keyMatch; } ;
struct TYPE_7__ {int hasTemplKeyPatterns; int nbKeys; TYPE_2__* style; } ;

/* Variables and functions */
 TYPE_2__* xsltNextImport (TYPE_2__*) ; 

__attribute__((used)) static int
xsltCountKeys(xsltTransformContextPtr ctxt)
{
    xsltStylesheetPtr style;
    xsltKeyDefPtr keyd;

    if (ctxt == NULL)
	return(-1);

    /*
    * Do we have those nastly templates with a key() in the match pattern?
    */
    ctxt->hasTemplKeyPatterns = 0;
    style = ctxt->style;
    while (style != NULL) {
	if (style->keyMatch != NULL) {
	    ctxt->hasTemplKeyPatterns = 1;
	    break;
	}
	style = xsltNextImport(style);
    }
    /*
    * Count number of key declarations.
    */
    ctxt->nbKeys = 0;
    style = ctxt->style;
    while (style != NULL) {
	keyd = style->keys;
	while (keyd) {
	    ctxt->nbKeys++;
	    keyd = keyd->next;
	}
	style = xsltNextImport(style);
    }
    return(ctxt->nbKeys);
}