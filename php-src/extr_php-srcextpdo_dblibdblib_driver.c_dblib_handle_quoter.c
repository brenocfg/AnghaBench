#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int zend_bool ;
struct TYPE_4__ {scalar_t__ assume_national_character_set_strings; } ;
typedef  TYPE_1__ pdo_dblib_db_handle ;
struct TYPE_5__ {scalar_t__ driver_data; } ;
typedef  TYPE_2__ pdo_dbh_t ;
typedef  enum pdo_param_type { ____Placeholder_pdo_param_type } pdo_param_type ;

/* Variables and functions */
 int PDO_PARAM_STR_CHAR ; 
 int PDO_PARAM_STR_NATL ; 
 char* emalloc (size_t) ; 

__attribute__((used)) static int dblib_handle_quoter(pdo_dbh_t *dbh, const char *unquoted, size_t unquotedlen, char **quoted, size_t *quotedlen, enum pdo_param_type paramtype)
{
	pdo_dblib_db_handle *H = (pdo_dblib_db_handle *)dbh->driver_data;
	zend_bool use_national_character_set = 0;

	size_t i;
	char * q;
	*quotedlen = 0;

	if (H->assume_national_character_set_strings) {
		use_national_character_set = 1;
	}
	if ((paramtype & PDO_PARAM_STR_NATL) == PDO_PARAM_STR_NATL) {
		use_national_character_set = 1;
	}
	if ((paramtype & PDO_PARAM_STR_CHAR) == PDO_PARAM_STR_CHAR) {
		use_national_character_set = 0;
	}

	/* Detect quoted length, adding extra char for doubled single quotes */
	for (i = 0; i < unquotedlen; i++) {
		if (unquoted[i] == '\'') ++*quotedlen;
		++*quotedlen;
	}

	*quotedlen += 2; /* +2 for opening, closing quotes */
	if (use_national_character_set) {
		++*quotedlen; /* N prefix */
	}
	q = *quoted = emalloc(*quotedlen + 1); /* Add byte for terminal null */
	if (use_national_character_set) {
		*q++ = 'N';
	}
	*q++ = '\'';

	for (i = 0; i < unquotedlen; i++) {
		if (unquoted[i] == '\'') {
			*q++ = '\'';
			*q++ = '\'';
		} else {
			*q++ = unquoted[i];
		}
	}
	*q++ = '\'';

	*q = 0;

	return 1;
}