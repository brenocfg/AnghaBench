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
typedef  int /*<<< orphan*/ * xsltAttrSetPtr ;
typedef  int /*<<< orphan*/  xsltAttrSet ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xmlMalloc (int) ; 
 int /*<<< orphan*/  xsltGenericError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xsltGenericErrorContext ; 

__attribute__((used)) static xsltAttrSetPtr
xsltNewAttrSet() {
    xsltAttrSetPtr cur;

    cur = (xsltAttrSetPtr) xmlMalloc(sizeof(xsltAttrSet));
    if (cur == NULL) {
        xsltGenericError(xsltGenericErrorContext,
		"xsltNewAttrSet : malloc failed\n");
	return(NULL);
    }
    memset(cur, 0, sizeof(xsltAttrSet));
    return(cur);
}