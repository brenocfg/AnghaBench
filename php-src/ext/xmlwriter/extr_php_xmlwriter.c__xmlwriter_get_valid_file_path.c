#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_stat_t ;
struct TYPE_5__ {int /*<<< orphan*/ * scheme; } ;
typedef  TYPE_1__ xmlURI ;
typedef  int /*<<< orphan*/  xmlChar ;

/* Variables and functions */
 int MAXPATHLEN ; 
 int /*<<< orphan*/  VCWD_REALPATH (char*,char*) ; 
 int /*<<< orphan*/  expand_filepath (char*,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int /*<<< orphan*/ ) ; 
 size_t php_dirname (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ php_sys_stat (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncasecmp (char*,char*,int) ; 
 TYPE_1__* xmlCreateURI () ; 
 int /*<<< orphan*/  xmlFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFreeURI (TYPE_1__*) ; 
 int /*<<< orphan*/  xmlParseURIReference (TYPE_1__*,char*) ; 
 int /*<<< orphan*/ * xmlURIEscapeStr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *_xmlwriter_get_valid_file_path(char *source, char *resolved_path, int resolved_path_len ) {
	xmlURI *uri;
	xmlChar *escsource;
	char *file_dest;
	int isFileUri = 0;

	uri = xmlCreateURI();
	escsource = xmlURIEscapeStr((xmlChar *)source, (xmlChar *) ":");
	xmlParseURIReference(uri, (char *)escsource);
	xmlFree(escsource);

	if (uri->scheme != NULL) {
		/* absolute file uris - libxml only supports localhost or empty host */
		if (strncasecmp(source, "file:///", 8) == 0) {
			if (source[sizeof("file:///") - 1] == '\0') {
				xmlFreeURI(uri);
				return NULL;
			}
			isFileUri = 1;
#ifdef PHP_WIN32
			source += 8;
#else
			source += 7;
#endif
		} else if (strncasecmp(source, "file://localhost/",17) == 0) {
			if (source[sizeof("file://localhost/") - 1] == '\0') {
				xmlFreeURI(uri);
				return NULL;
			}

			isFileUri = 1;
#ifdef PHP_WIN32
			source += 17;
#else
			source += 16;
#endif
		}
	}

	if ((uri->scheme == NULL || isFileUri)) {
		char file_dirname[MAXPATHLEN];
		size_t dir_len;

		if (!VCWD_REALPATH(source, resolved_path) && !expand_filepath(source, resolved_path)) {
			xmlFreeURI(uri);
			return NULL;
		}

		memcpy(file_dirname, source, strlen(source));
		dir_len = php_dirname(file_dirname, strlen(source));

		if (dir_len > 0) {
			zend_stat_t buf;
			if (php_sys_stat(file_dirname, &buf) != 0) {
				xmlFreeURI(uri);
				return NULL;
			}
		}

		file_dest = resolved_path;
	} else {
		file_dest = source;
	}

	xmlFreeURI(uri);

	return file_dest;
}