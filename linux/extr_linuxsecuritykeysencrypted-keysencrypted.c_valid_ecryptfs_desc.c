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
 int EINVAL ; 
 int KEY_ECRYPTFS_DESC_LEN ; 
 int /*<<< orphan*/  isxdigit (char const) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int valid_ecryptfs_desc(const char *ecryptfs_desc)
{
	int i;

	if (strlen(ecryptfs_desc) != KEY_ECRYPTFS_DESC_LEN) {
		pr_err("encrypted_key: key description must be %d hexadecimal "
		       "characters long\n", KEY_ECRYPTFS_DESC_LEN);
		return -EINVAL;
	}

	for (i = 0; i < KEY_ECRYPTFS_DESC_LEN; i++) {
		if (!isxdigit(ecryptfs_desc[i])) {
			pr_err("encrypted_key: key description must contain "
			       "only hexadecimal characters\n");
			return -EINVAL;
		}
	}

	return 0;
}