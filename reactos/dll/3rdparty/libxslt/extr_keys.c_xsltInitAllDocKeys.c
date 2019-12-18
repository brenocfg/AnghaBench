#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* xsltTransformContextPtr ;
typedef  TYPE_3__* xsltStylesheetPtr ;
typedef  TYPE_4__* xsltKeyTablePtr ;
typedef  TYPE_5__* xsltKeyDefPtr ;
struct TYPE_14__ {char* name; char* nameURI; struct TYPE_14__* next; } ;
struct TYPE_13__ {struct TYPE_13__* next; int /*<<< orphan*/ * nameURI; int /*<<< orphan*/ * name; } ;
struct TYPE_12__ {scalar_t__ keys; } ;
struct TYPE_11__ {int nbKeys; TYPE_1__* document; TYPE_3__* style; } ;
struct TYPE_10__ {int nbKeysComputed; scalar_t__ keys; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ xmlStrEqual (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsltInitDocKeyTable (TYPE_2__*,char*,char*) ; 
 TYPE_3__* xsltNextImport (TYPE_3__*) ; 

int
xsltInitAllDocKeys(xsltTransformContextPtr ctxt)
{
    xsltStylesheetPtr style;
    xsltKeyDefPtr keyd;
    xsltKeyTablePtr table;

    if (ctxt == NULL)
	return(-1);

#ifdef KEY_INIT_DEBUG
fprintf(stderr, "xsltInitAllDocKeys %d %d\n",
        ctxt->document->nbKeysComputed, ctxt->nbKeys);
#endif

    if (ctxt->document->nbKeysComputed == ctxt->nbKeys)
	return(0);


    /*
    * TODO: This could be further optimized
    */
    style = ctxt->style;
    while (style) {
	keyd = (xsltKeyDefPtr) style->keys;
	while (keyd != NULL) {
#ifdef KEY_INIT_DEBUG
fprintf(stderr, "Init key %s\n", keyd->name);
#endif
	    /*
	    * Check if keys with this QName have been already
	    * computed.
	    */
	    table = (xsltKeyTablePtr) ctxt->document->keys;
	    while (table) {
		if (((keyd->nameURI != NULL) == (table->nameURI != NULL)) &&
		    xmlStrEqual(keyd->name, table->name) &&
		    xmlStrEqual(keyd->nameURI, table->nameURI))
		{
		    break;
		}
		table = table->next;
	    }
	    if (table == NULL) {
		/*
		* Keys with this QName have not been yet computed.
		*/
		xsltInitDocKeyTable(ctxt, keyd->name, keyd->nameURI);
	    }
	    keyd = keyd->next;
	}
	style = xsltNextImport(style);
    }
#ifdef KEY_INIT_DEBUG
fprintf(stderr, "xsltInitAllDocKeys: done\n");
#endif
    return(0);
}