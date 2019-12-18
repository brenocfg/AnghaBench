#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int zend_bool ;
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_6__ {TYPE_1__* iPAddress; int /*<<< orphan*/  dNSName; } ;
struct TYPE_7__ {scalar_t__ type; TYPE_2__ d; } ;
struct TYPE_5__ {int length; int* data; } ;
typedef  int /*<<< orphan*/  GENERAL_NAMES ;
typedef  TYPE_3__ GENERAL_NAME ;

/* Variables and functions */
 scalar_t__ ASN1_STRING_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASN1_STRING_to_UTF8 (unsigned char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GENERAL_NAME_free ; 
 scalar_t__ GEN_DNS ; 
 scalar_t__ GEN_IPADD ; 
 int /*<<< orphan*/  NID_subject_alt_name ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 int /*<<< orphan*/ * X509_get_ext_d2i (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ php_openssl_matches_wildcard_name (char const*,char const*) ; 
 int sk_GENERAL_NAME_num (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_GENERAL_NAME_pop_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* sk_GENERAL_NAME_value (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int,int) ; 
 scalar_t__ strcasecmp (char const*,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static zend_bool php_openssl_matches_san_list(X509 *peer, const char *subject_name) /* {{{ */
{
	int i, len;
	unsigned char *cert_name = NULL;
	char ipbuffer[64];

	GENERAL_NAMES *alt_names = X509_get_ext_d2i(peer, NID_subject_alt_name, 0, 0);
	int alt_name_count = sk_GENERAL_NAME_num(alt_names);

	for (i = 0; i < alt_name_count; i++) {
		GENERAL_NAME *san = sk_GENERAL_NAME_value(alt_names, i);

		if (san->type == GEN_DNS) {
			ASN1_STRING_to_UTF8(&cert_name, san->d.dNSName);
			if ((size_t)ASN1_STRING_length(san->d.dNSName) != strlen((const char*)cert_name)) {
				OPENSSL_free(cert_name);
				/* prevent null-byte poisoning*/
				continue;
			}

			/* accommodate valid FQDN entries ending in "." */
			len = strlen((const char*)cert_name);
			if (len && strcmp((const char *)&cert_name[len-1], ".") == 0) {
				cert_name[len-1] = '\0';
			}

			if (php_openssl_matches_wildcard_name(subject_name, (const char *)cert_name)) {
				OPENSSL_free(cert_name);
				sk_GENERAL_NAME_pop_free(alt_names, GENERAL_NAME_free);

				return 1;
			}
			OPENSSL_free(cert_name);
		} else if (san->type == GEN_IPADD) {
			if (san->d.iPAddress->length == 4) {
				sprintf(ipbuffer, "%d.%d.%d.%d",
					san->d.iPAddress->data[0],
					san->d.iPAddress->data[1],
					san->d.iPAddress->data[2],
					san->d.iPAddress->data[3]
				);
				if (strcasecmp(subject_name, (const char*)ipbuffer) == 0) {
					sk_GENERAL_NAME_pop_free(alt_names, GENERAL_NAME_free);

					return 1;
				}
			}
			/* No, we aren't bothering to check IPv6 addresses. Why?
			 * Because IP SAN names are officially deprecated and are
			 * not allowed by CAs starting in 2015. Deal with it.
			 */
		}
	}

	sk_GENERAL_NAME_pop_free(alt_names, GENERAL_NAME_free);

	return 0;
}