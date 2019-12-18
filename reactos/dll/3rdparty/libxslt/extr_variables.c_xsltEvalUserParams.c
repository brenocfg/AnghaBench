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
typedef  int /*<<< orphan*/  xsltTransformContextPtr ;
typedef  int /*<<< orphan*/  xmlChar ;

/* Variables and functions */
 scalar_t__ xsltEvalOneUserParam (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

int
xsltEvalUserParams(xsltTransformContextPtr ctxt, const char **params) {
    int indx = 0;
    const xmlChar *name;
    const xmlChar *value;

    if (params == NULL)
	return(0);
    while (params[indx] != NULL) {
	name = (const xmlChar *) params[indx++];
	value = (const xmlChar *) params[indx++];
	if (xsltEvalOneUserParam(ctxt, name, value) != 0)
	    return(-1);
    }
    return 0;
}