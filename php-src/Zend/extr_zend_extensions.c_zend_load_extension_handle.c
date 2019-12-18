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
struct TYPE_4__ {scalar_t__ zend_extension_api_no; char* build_id; } ;
typedef  TYPE_1__ zend_extension_version_info ;
struct TYPE_5__ {scalar_t__ (* api_no_check ) (scalar_t__) ;char* name; char* author; char* URL; scalar_t__ (* build_id_check ) (char*) ;} ;
typedef  TYPE_2__ zend_extension ;
typedef  int /*<<< orphan*/  DL_HANDLE ;

/* Variables and functions */
 scalar_t__ DL_FETCH_SYMBOL (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DL_UNLOAD (int /*<<< orphan*/ ) ; 
 int FAILURE ; 
 scalar_t__ SUCCESS ; 
 scalar_t__ ZEND_EXTENSION_API_NO ; 
 char* ZEND_EXTENSION_BUILD_ID ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ stub1 (scalar_t__) ; 
 scalar_t__ stub2 (char*) ; 
 scalar_t__ zend_get_extension (char*) ; 
 int zend_register_extension (TYPE_2__*,int /*<<< orphan*/ ) ; 

int zend_load_extension_handle(DL_HANDLE handle, const char *path)
{
#if ZEND_EXTENSIONS_SUPPORT
	zend_extension *new_extension;
	zend_extension_version_info *extension_version_info;

	extension_version_info = (zend_extension_version_info *) DL_FETCH_SYMBOL(handle, "extension_version_info");
	if (!extension_version_info) {
		extension_version_info = (zend_extension_version_info *) DL_FETCH_SYMBOL(handle, "_extension_version_info");
	}
	new_extension = (zend_extension *) DL_FETCH_SYMBOL(handle, "zend_extension_entry");
	if (!new_extension) {
		new_extension = (zend_extension *) DL_FETCH_SYMBOL(handle, "_zend_extension_entry");
	}
	if (!extension_version_info || !new_extension) {
		fprintf(stderr, "%s doesn't appear to be a valid Zend extension\n", path);
/* See http://support.microsoft.com/kb/190351 */
#ifdef ZEND_WIN32
		fflush(stderr);
#endif
		DL_UNLOAD(handle);
		return FAILURE;
	}

	/* allow extension to proclaim compatibility with any Zend version */
	if (extension_version_info->zend_extension_api_no != ZEND_EXTENSION_API_NO &&(!new_extension->api_no_check || new_extension->api_no_check(ZEND_EXTENSION_API_NO) != SUCCESS)) {
		if (extension_version_info->zend_extension_api_no > ZEND_EXTENSION_API_NO) {
			fprintf(stderr, "%s requires Zend Engine API version %d.\n"
					"The Zend Engine API version %d which is installed, is outdated.\n\n",
					new_extension->name,
					extension_version_info->zend_extension_api_no,
					ZEND_EXTENSION_API_NO);
/* See http://support.microsoft.com/kb/190351 */
#ifdef ZEND_WIN32
			fflush(stderr);
#endif
			DL_UNLOAD(handle);
			return FAILURE;
		} else if (extension_version_info->zend_extension_api_no < ZEND_EXTENSION_API_NO) {
			fprintf(stderr, "%s requires Zend Engine API version %d.\n"
					"The Zend Engine API version %d which is installed, is newer.\n"
					"Contact %s at %s for a later version of %s.\n\n",
					new_extension->name,
					extension_version_info->zend_extension_api_no,
					ZEND_EXTENSION_API_NO,
					new_extension->author,
					new_extension->URL,
					new_extension->name);
/* See http://support.microsoft.com/kb/190351 */
#ifdef ZEND_WIN32
			fflush(stderr);
#endif
			DL_UNLOAD(handle);
			return FAILURE;
		}
	} else if (strcmp(ZEND_EXTENSION_BUILD_ID, extension_version_info->build_id) &&
	           (!new_extension->build_id_check || new_extension->build_id_check(ZEND_EXTENSION_BUILD_ID) != SUCCESS)) {
		fprintf(stderr, "Cannot load %s - it was built with configuration %s, whereas running engine is %s\n",
					new_extension->name, extension_version_info->build_id, ZEND_EXTENSION_BUILD_ID);
/* See http://support.microsoft.com/kb/190351 */
#ifdef ZEND_WIN32
		fflush(stderr);
#endif
		DL_UNLOAD(handle);
		return FAILURE;
	} else if (zend_get_extension(new_extension->name)) {
		fprintf(stderr, "Cannot load %s - it was already loaded\n", new_extension->name);
/* See http://support.microsoft.com/kb/190351 */
#ifdef ZEND_WIN32
		fflush(stderr);
#endif
		DL_UNLOAD(handle);
		return FAILURE;
	}

	return zend_register_extension(new_extension, handle);
#else
	fprintf(stderr, "Extensions are not supported on this platform.\n");
/* See http://support.microsoft.com/kb/190351 */
#ifdef ZEND_WIN32
	fflush(stderr);
#endif
	return FAILURE;
#endif
}