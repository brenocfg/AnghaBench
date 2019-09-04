#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  php_stream ;
struct TYPE_3__ {char* url_name; int /*<<< orphan*/  ssl_handle; } ;
typedef  TYPE_1__ php_openssl_netstream_data_t ;

/* Variables and functions */
 scalar_t__ GET_VER_OPT (char*) ; 
 int /*<<< orphan*/  GET_VER_OPT_STRING (char*,char*) ; 
 int /*<<< orphan*/  SSL_set_tlsext_host_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zend_is_true (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void php_openssl_enable_client_sni(php_stream *stream, php_openssl_netstream_data_t *sslsock) /* {{{ */
{
	zval *val;
	char *sni_server_name;

	/* If SNI is explicitly disabled we're finished here */
	if (GET_VER_OPT("SNI_enabled") && !zend_is_true(val)) {
		return;
	}

	sni_server_name = sslsock->url_name;

	GET_VER_OPT_STRING("peer_name", sni_server_name);

	if (sni_server_name) {
		SSL_set_tlsext_host_name(sslsock->ssl_handle, sni_server_name);
	}
}