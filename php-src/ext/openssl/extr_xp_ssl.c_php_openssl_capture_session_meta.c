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
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_array ;
typedef  int /*<<< orphan*/  SSL_CIPHER ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
#define  SSL3_VERSION 132 
 int /*<<< orphan*/  SSL_CIPHER_get_bits (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ SSL_CIPHER_get_name (int /*<<< orphan*/  const*) ; 
 char* SSL_CIPHER_get_version (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * SSL_get_current_cipher (int /*<<< orphan*/ *) ; 
 long SSL_version (int /*<<< orphan*/ *) ; 
#define  TLS1_1_VERSION 131 
#define  TLS1_2_VERSION 130 
#define  TLS1_3_VERSION 129 
#define  TLS1_VERSION 128 
 int /*<<< orphan*/ * Z_ARR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_assoc_long (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_assoc_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  array_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static zend_array *php_openssl_capture_session_meta(SSL *ssl_handle) /* {{{ */
{
	zval meta_arr;
	char *proto_str;
	long proto = SSL_version(ssl_handle);
	const SSL_CIPHER *cipher = SSL_get_current_cipher(ssl_handle);

	switch (proto) {
#ifdef HAVE_TLS13
		case TLS1_3_VERSION:
			proto_str = "TLSv1.3";
			break;
#endif
#ifdef HAVE_TLS12
		case TLS1_2_VERSION:
			proto_str = "TLSv1.2";
			break;
#endif
#ifdef HAVE_TLS11
		case TLS1_1_VERSION:
			proto_str = "TLSv1.1";
			break;
#endif
		case TLS1_VERSION:
			proto_str = "TLSv1";
			break;
#ifdef HAVE_SSL3
		case SSL3_VERSION:
			proto_str = "SSLv3";
			break;
#endif
		default: proto_str = "UNKNOWN";
	}

	array_init(&meta_arr);
	add_assoc_string(&meta_arr, "protocol", proto_str);
	add_assoc_string(&meta_arr, "cipher_name", (char *) SSL_CIPHER_get_name(cipher));
	add_assoc_long(&meta_arr, "cipher_bits", SSL_CIPHER_get_bits(cipher, NULL));
	add_assoc_string(&meta_arr, "cipher_version", SSL_CIPHER_get_version(cipher));

	return Z_ARR(meta_arr);
}