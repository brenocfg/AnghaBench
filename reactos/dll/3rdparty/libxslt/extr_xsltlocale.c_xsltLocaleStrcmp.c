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

/* Variables and functions */
 int CompareStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,int) ; 
 int xmlStrcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xsltTransformError (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

int
xsltLocaleStrcmp(xsltLocale locale, const xsltLocaleChar *str1, const xsltLocaleChar *str2) {
    (void)locale;
#ifdef XSLT_LOCALE_WINAPI
{
    int ret;
    if (str1 == str2) return(0);
    if (str1 == NULL) return(-1);
    if (str2 == NULL) return(1);
    ret = CompareStringW(locale, 0, str1, -1, str2, -1);
    if (ret == 0) {
        xsltTransformError(NULL, NULL, NULL, "xsltLocaleStrcmp : CompareStringW fail\n");
        return(0);
    }
    return(ret - 2);
}
#else
    return(xmlStrcmp(str1, str2));
#endif
}