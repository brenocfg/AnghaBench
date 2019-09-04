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

/* Variables and functions */
#define  SQLITE_ATTACH 129 
#define  SQLITE_COPY 128 
 int SQLITE_DENY ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  efree (char*) ; 
 char* make_filename_safe (char const*) ; 

__attribute__((used)) static int authorizer(void *autharg, int access_type, const char *arg3, const char *arg4,
		const char *arg5, const char *arg6)
{
	char *filename;
	switch (access_type) {
		case SQLITE_COPY: {
					filename = make_filename_safe(arg4);
			if (!filename) {
				return SQLITE_DENY;
			}
			efree(filename);
			return SQLITE_OK;
		}

		case SQLITE_ATTACH: {
					filename = make_filename_safe(arg3);
			if (!filename) {
				return SQLITE_DENY;
			}
			efree(filename);
			return SQLITE_OK;
		}

		default:
			/* access allowed */
			return SQLITE_OK;
	}
}