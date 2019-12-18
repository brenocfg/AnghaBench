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
typedef  int /*<<< orphan*/  xsltLocaleChar ;
typedef  int /*<<< orphan*/  xsltLocale ;
typedef  int /*<<< orphan*/  xmlChar ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UTF8 ; 
 size_t MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,size_t) ; 
 int strxfrm_l (char*,char const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlFree (int /*<<< orphan*/ *) ; 
 scalar_t__ xmlMalloc (size_t) ; 
 int /*<<< orphan*/  xsltTransformError (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

xsltLocaleChar *
xsltStrxfrm(xsltLocale locale, const xmlChar *string)
{
#ifdef XSLT_LOCALE_NONE
    return(NULL);
#else
    size_t xstrlen, r;
    xsltLocaleChar *xstr;

#ifdef XSLT_LOCALE_POSIX
    xstrlen = strxfrm_l(NULL, (const char *)string, 0, locale) + 1;
    xstr = (xsltLocaleChar *) xmlMalloc(xstrlen);
    if (xstr == NULL) {
	xsltTransformError(NULL, NULL, NULL,
	    "xsltStrxfrm : out of memory error\n");
	return(NULL);
    }

    r = strxfrm_l((char *)xstr, (const char *)string, xstrlen, locale);
#endif

#ifdef XSLT_LOCALE_WINAPI
    xstrlen = MultiByteToWideChar(CP_UTF8, 0, (char *) string, -1, NULL, 0);
    if (xstrlen == 0) {
        xsltTransformError(NULL, NULL, NULL, "xsltStrxfrm : MultiByteToWideChar check failed\n");
        return(NULL);
    }
    xstr = (xsltLocaleChar*) xmlMalloc(xstrlen * sizeof(xsltLocaleChar));
    if (xstr == NULL) {
        xsltTransformError(NULL, NULL, NULL, "xsltStrxfrm : out of memory\n");
        return(NULL);
    }
    r = MultiByteToWideChar(CP_UTF8, 0, (char *) string, -1, xstr, xstrlen);
    if (r == 0) {
        xsltTransformError(NULL, NULL, NULL, "xsltStrxfrm : MultiByteToWideChar failed\n");
        xmlFree(xstr);
        return(NULL);
    }
    return(xstr);
#endif /* XSLT_LOCALE_WINAPI */

    if (r >= xstrlen) {
	xsltTransformError(NULL, NULL, NULL, "xsltStrxfrm : strxfrm failed\n");
        xmlFree(xstr);
        return(NULL);
    }

    return(xstr);
#endif /* XSLT_LOCALE_NONE */
}