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
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 int FAILURE ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  PHP_OPENSSL_RAND_ADD_TIME () ; 
 char* RAND_file_name (char*,int) ; 
 int /*<<< orphan*/  RAND_write_file (char const*) ; 
 int SUCCESS ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  php_openssl_store_errors () ; 

__attribute__((used)) static int php_openssl_write_rand_file(const char * file, int egdsocket, int seeded) /* {{{ */
{
	char buffer[MAXPATHLEN];


	if (egdsocket || !seeded) {
		/* if we did not manage to read the seed file, we should not write
		 * a low-entropy seed file back */
		return FAILURE;
	}
	if (file == NULL) {
		file = RAND_file_name(buffer, sizeof(buffer));
	}
	PHP_OPENSSL_RAND_ADD_TIME();
	if (file == NULL || !RAND_write_file(file)) {
		php_openssl_store_errors();
		php_error_docref(NULL, E_WARNING, "unable to write random state");
		return FAILURE;
	}
	return SUCCESS;
}