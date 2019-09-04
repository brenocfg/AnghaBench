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
typedef  int zend_bool ;
typedef  int ptrdiff_t ;

/* Variables and functions */
 int /*<<< orphan*/ * memchr (char const*,char,size_t) ; 
 scalar_t__ strcasecmp (char const*,char const*) ; 
 char* strchr (char const*,char) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncasecmp (char const*,char const*,int) ; 

__attribute__((used)) static zend_bool php_openssl_matches_wildcard_name(const char *subjectname, const char *certname) /* {{{ */
{
	char *wildcard = NULL;
	ptrdiff_t prefix_len;
	size_t suffix_len, subject_len;

	if (strcasecmp(subjectname, certname) == 0) {
		return 1;
	}

	/* wildcard, if present, must only be present in the left-most component */
	if (!(wildcard = strchr(certname, '*')) || memchr(certname, '.', wildcard - certname)) {
		return 0;
	}

	/* 1) prefix, if not empty, must match subject */
	prefix_len = wildcard - certname;
	if (prefix_len && strncasecmp(subjectname, certname, prefix_len) != 0) {
		return 0;
	}

	suffix_len = strlen(wildcard + 1);
	subject_len = strlen(subjectname);
	if (suffix_len <= subject_len) {
		/* 2) suffix must match
		 * 3) no . between prefix and suffix
		 **/
		return strcasecmp(wildcard + 1, subjectname + subject_len - suffix_len) == 0 &&
			memchr(subjectname + prefix_len, '.', subject_len - suffix_len - prefix_len) == NULL;
	}

	return 0;
}