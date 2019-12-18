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
typedef  char xmlChar ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ safe_emalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 scalar_t__ xmlStrchr (char const*,char) ; 
 int xmlStrlen (char const*) ; 

__attribute__((used)) static char *php_xsl_xslt_string_to_xpathexpr(const char *str)
{
	const xmlChar *string = (const xmlChar *)str;

	xmlChar *value;
	int str_len;

	str_len = xmlStrlen(string) + 3;

	if (xmlStrchr(string, '"')) {
		if (xmlStrchr(string, '\'')) {
			php_error_docref(NULL, E_WARNING, "Cannot create XPath expression (string contains both quote and double-quotes)");
			return NULL;
		}
		value = (xmlChar*) safe_emalloc (str_len, sizeof(xmlChar), 0);
		snprintf((char*)value, str_len, "'%s'", string);
	} else {
		value = (xmlChar*) safe_emalloc (str_len, sizeof(xmlChar), 0);
		snprintf((char *)value, str_len, "\"%s\"", string);
	}
	return (char *) value;
}