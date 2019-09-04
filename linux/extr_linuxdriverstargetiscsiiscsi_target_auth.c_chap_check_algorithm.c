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
 int CHAP_DIGEST_MD5 ; 
 int CHAP_DIGEST_UNKNOWN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrdup (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int chap_check_algorithm(const char *a_str)
{
	char *tmp, *orig, *token;

	tmp = kstrdup(a_str, GFP_KERNEL);
	if (!tmp) {
		pr_err("Memory allocation failed for CHAP_A temporary buffer\n");
		return CHAP_DIGEST_UNKNOWN;
	}
	orig = tmp;

	token = strsep(&tmp, "=");
	if (!token)
		goto out;

	if (strcmp(token, "CHAP_A")) {
		pr_err("Unable to locate CHAP_A key\n");
		goto out;
	}
	while (token) {
		token = strsep(&tmp, ",");
		if (!token)
			goto out;

		if (!strncmp(token, "5", 1)) {
			pr_debug("Selected MD5 Algorithm\n");
			kfree(orig);
			return CHAP_DIGEST_MD5;
		}
	}
out:
	kfree(orig);
	return CHAP_DIGEST_UNKNOWN;
}