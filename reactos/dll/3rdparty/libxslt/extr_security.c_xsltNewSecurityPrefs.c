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
typedef  int /*<<< orphan*/ * xsltSecurityPrefsPtr ;
typedef  int /*<<< orphan*/  xsltSecurityPrefs ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xmlMalloc (int) ; 
 int /*<<< orphan*/  xsltInitGlobals () ; 
 int /*<<< orphan*/  xsltTransformError (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

xsltSecurityPrefsPtr
xsltNewSecurityPrefs(void) {
    xsltSecurityPrefsPtr ret;

    xsltInitGlobals();

    ret = (xsltSecurityPrefsPtr) xmlMalloc(sizeof(xsltSecurityPrefs));
    if (ret == NULL) {
	xsltTransformError(NULL, NULL, NULL,
		"xsltNewSecurityPrefs : malloc failed\n");
	return(NULL);
    }
    memset(ret, 0, sizeof(xsltSecurityPrefs));
    return(ret);
}