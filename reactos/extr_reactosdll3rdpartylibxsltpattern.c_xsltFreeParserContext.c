#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/ * xsltParserContextPtr ;
typedef  int /*<<< orphan*/  xsltParserContext ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  xmlFree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
xsltFreeParserContext(xsltParserContextPtr ctxt) {
    if (ctxt == NULL)
	return;
    memset(ctxt, -1, sizeof(xsltParserContext));
    xmlFree(ctxt);
}