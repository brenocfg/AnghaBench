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
typedef  int /*<<< orphan*/  xsltLocale ;
typedef  int /*<<< orphan*/  xmlChar ;

/* Variables and functions */

xsltLocale
xsltNewLocale(const xmlChar *languageTag) {
#ifdef XSLT_LOCALE_POSIX
    xsltLocale locale;
    char localeName[XSLTMAX_LANGTAGLEN+6]; /* 6 chars for ".utf8\0" */
    const xmlChar *p = languageTag;
    const char *region = NULL;
    char *q = localeName;
    int i, llen;

    /* Convert something like "pt-br" to "pt_BR.utf8" */

    if (languageTag == NULL)
	return(NULL);

    for (i=0; i<XSLTMAX_ISO639LANGLEN && ISALPHA(*p); ++i)
	*q++ = TOLOWER(*p++);

    if (i == 0)
	return(NULL);

    llen = i;

    if (*p) {
	if (*p++ != '-')
	    return(NULL);
        *q++ = '_';

	for (i=0; i<XSLTMAX_ISO3166CNTRYLEN && ISALPHA(*p); ++i)
	    *q++ = TOUPPER(*p++);

	if (i == 0 || *p)
	    return(NULL);

        memcpy(q, ".utf8", 6);
        locale = newlocale(LC_COLLATE_MASK, localeName, NULL);
        if (locale != NULL)
            return(locale);

        /* Continue without using country code */

        q = localeName + llen;
    }

    /* Try locale without territory, e.g. for Esperanto (eo) */

    memcpy(q, ".utf8", 6);
    locale = newlocale(LC_COLLATE_MASK, localeName, NULL);
    if (locale != NULL)
        return(locale);

    /* Try to find most common country for language */

    if (llen != 2)
        return(NULL);

    region = (char *)xsltDefaultRegion((xmlChar *)localeName);
    if (region == NULL)
        return(NULL);

    q = localeName + llen;
    *q++ = '_';
    *q++ = region[0];
    *q++ = region[1];
    memcpy(q, ".utf8", 6);
    locale = newlocale(LC_COLLATE_MASK, localeName, NULL);

    return(locale);
#endif

#ifdef XSLT_LOCALE_WINAPI
{
    xsltLocale    locale = (xsltLocale)0;
    xmlChar       localeName[XSLTMAX_LANGTAGLEN+1];
    xmlChar       *q = localeName;
    const xmlChar *p = languageTag;
    int           i, llen;
    const xmlChar *region = NULL;

    if (languageTag == NULL) goto end;

    xsltEnumSupportedLocales();

    for (i=0; i<XSLTMAX_ISO639LANGLEN && ISALPHA(*p); ++i)
	*q++ = TOLOWER(*p++);
    if (i == 0) goto end;

    llen = i;
    *q++ = '-';
    if (*p) { /*if country tag is given*/
	if (*p++ != '-') goto end;

	for (i=0; i<XSLTMAX_ISO3166CNTRYLEN && ISALPHA(*p); ++i)
	    *q++ = TOUPPER(*p++);
	if (i == 0 || *p) goto end;

	*q = '\0';
	locale = xslt_locale_WINAPI(localeName);
	if (locale != (xsltLocale)0) goto end;
    }
    /* Try to find most common country for language */
    region = xsltDefaultRegion(localeName);
    if (region == NULL) goto end;

    strcpy((char *) localeName + llen + 1, (char *) region);
    locale = xslt_locale_WINAPI(localeName);
end:
    return(locale);
}
#endif

#ifdef XSLT_LOCALE_NONE
    return(NULL);
#endif
}