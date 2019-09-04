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
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  X509 ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * php_openssl_x509_fingerprint (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int strcasecmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_string_release_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int php_openssl_x509_fingerprint_cmp(X509 *peer, const char *method, const char *expected)
{
	zend_string *fingerprint;
	int result = -1;

	fingerprint = php_openssl_x509_fingerprint(peer, method, 0);
	if (fingerprint) {
		result = strcasecmp(expected, ZSTR_VAL(fingerprint));
		zend_string_release_ex(fingerprint, 0);
	}

	return result;
}