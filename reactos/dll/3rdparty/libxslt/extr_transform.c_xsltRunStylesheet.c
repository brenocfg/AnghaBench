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
typedef  int /*<<< orphan*/  xsltStylesheetPtr ;
typedef  int /*<<< orphan*/  xmlSAXHandlerPtr ;
typedef  int /*<<< orphan*/  xmlOutputBufferPtr ;
typedef  int /*<<< orphan*/  xmlDocPtr ;

/* Variables and functions */
 int xsltRunStylesheetUser (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const**,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
xsltRunStylesheet(xsltStylesheetPtr style, xmlDocPtr doc,
                  const char **params, const char *output,
                  xmlSAXHandlerPtr SAX, xmlOutputBufferPtr IObuf)
{
    return(xsltRunStylesheetUser(style, doc, params, output, SAX, IObuf,
		                 NULL, NULL));
}