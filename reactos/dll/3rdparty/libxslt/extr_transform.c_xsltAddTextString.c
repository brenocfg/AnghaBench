#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltTransformContextPtr ;
typedef  TYPE_2__* xmlNodePtr ;
typedef  scalar_t__ xmlChar ;
struct TYPE_10__ {scalar_t__* content; } ;
struct TYPE_9__ {int lasttuse; int lasttsize; scalar_t__* lasttext; } ;

/* Variables and functions */
 int INT_MAX ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__ const*,int) ; 
 int /*<<< orphan*/  xmlNodeAddContent (TYPE_2__*,scalar_t__ const*) ; 
 scalar_t__ xmlRealloc (scalar_t__*,int) ; 
 int xmlStrlen (scalar_t__*) ; 
 int /*<<< orphan*/  xsltTransformError (TYPE_1__*,int /*<<< orphan*/ *,TYPE_2__*,char*) ; 

__attribute__((used)) static xmlNodePtr
xsltAddTextString(xsltTransformContextPtr ctxt, xmlNodePtr target,
		  const xmlChar *string, int len) {
    /*
     * optimization
     */
    if ((len <= 0) || (string == NULL) || (target == NULL))
        return(target);

    if (ctxt->lasttext == target->content) {
        int minSize;

        /* Check for integer overflow accounting for NUL terminator. */
        if (len >= INT_MAX - ctxt->lasttuse) {
            xsltTransformError(ctxt, NULL, target,
                "xsltCopyText: text allocation failed\n");
            return(NULL);
        }
        minSize = ctxt->lasttuse + len + 1;

        if (ctxt->lasttsize < minSize) {
	    xmlChar *newbuf;
	    int size;
            int extra;

            /* Double buffer size but increase by at least 100 bytes. */
            extra = minSize < 100 ? 100 : minSize;

            /* Check for integer overflow. */
            if (extra > INT_MAX - ctxt->lasttsize) {
                size = INT_MAX;
            }
            else {
                size = ctxt->lasttsize + extra;
            }

	    newbuf = (xmlChar *) xmlRealloc(target->content,size);
	    if (newbuf == NULL) {
		xsltTransformError(ctxt, NULL, target,
		 "xsltCopyText: text allocation failed\n");
		return(NULL);
	    }
	    ctxt->lasttsize = size;
	    ctxt->lasttext = newbuf;
	    target->content = newbuf;
	}
	memcpy(&(target->content[ctxt->lasttuse]), string, len);
	ctxt->lasttuse += len;
	target->content[ctxt->lasttuse] = 0;
    } else {
	xmlNodeAddContent(target, string);
	ctxt->lasttext = target->content;
	len = xmlStrlen(target->content);
	ctxt->lasttsize = len;
	ctxt->lasttuse = len;
    }
    return(target);
}