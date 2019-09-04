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
typedef  int /*<<< orphan*/  pdo_dbh_t ;
typedef  enum pdo_param_type { ____Placeholder_pdo_param_type } pdo_param_type ;

/* Variables and functions */
 char* emalloc (size_t) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 

__attribute__((used)) static int oci_handle_quoter(pdo_dbh_t *dbh, const char *unquoted, size_t unquotedlen, char **quoted, size_t *quotedlen, enum pdo_param_type paramtype ) /* {{{ */
{
	int qcount = 0;
	char const *cu, *l, *r;
	char *c;

	if (!unquotedlen) {
		*quotedlen = 2;
		*quoted = emalloc(*quotedlen+1);
		strcpy(*quoted, "''");
		return 1;
	}

	/* count single quotes */
	for (cu = unquoted; (cu = strchr(cu,'\'')); qcount++, cu++)
		; /* empty loop */

	*quotedlen = unquotedlen + qcount + 2;
	*quoted = c = emalloc(*quotedlen+1);
	*c++ = '\'';

	/* foreach (chunk that ends in a quote) */
	for (l = unquoted; (r = strchr(l,'\'')); l = r+1) {
		strncpy(c, l, r-l+1);
		c += (r-l+1);
		*c++ = '\'';			/* add second quote */
	}

    /* Copy remainder and add enclosing quote */
	strncpy(c, l, *quotedlen-(c-*quoted)-1);
	(*quoted)[*quotedlen-1] = '\'';
	(*quoted)[*quotedlen]   = '\0';

	return 1;
}