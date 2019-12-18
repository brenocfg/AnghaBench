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
 scalar_t__ RAND_egd (char const*) ; 
 char* RAND_file_name (char*,int) ; 
 int /*<<< orphan*/  RAND_load_file (char const*,int) ; 
 scalar_t__ RAND_status () ; 
 int SUCCESS ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  php_openssl_store_errors () ; 

__attribute__((used)) static int php_openssl_load_rand_file(const char * file, int *egdsocket, int *seeded) /* {{{ */
{
	char buffer[MAXPATHLEN];

	*egdsocket = 0;
	*seeded = 0;

	if (file == NULL) {
		file = RAND_file_name(buffer, sizeof(buffer));
#ifdef HAVE_RAND_EGD
	} else if (RAND_egd(file) > 0) {
		/* if the given filename is an EGD socket, don't
		 * write anything back to it */
		*egdsocket = 1;
		return SUCCESS;
#endif
	}
	if (file == NULL || !RAND_load_file(file, -1)) {
		if (RAND_status() == 0) {
			php_openssl_store_errors();
			php_error_docref(NULL, E_WARNING, "unable to load random state; not enough random data!");
			return FAILURE;
		}
		return FAILURE;
	}
	*seeded = 1;
	return SUCCESS;
}