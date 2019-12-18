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
typedef  int /*<<< orphan*/  sslbits_str ;
struct TYPE_3__ {int /*<<< orphan*/ * ssl; } ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 char const* SSL_get_cipher (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_get_cipher_bits (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ SSL_get_current_compression (int /*<<< orphan*/ *) ; 
 char const* SSL_get_version (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 scalar_t__ strcmp (char const*,char*) ; 

const char *
PQsslAttribute(PGconn *conn, const char *attribute_name)
{
	if (!conn)
		return NULL;
	if (conn->ssl == NULL)
		return NULL;

	if (strcmp(attribute_name, "library") == 0)
		return "OpenSSL";

	if (strcmp(attribute_name, "key_bits") == 0)
	{
		static char sslbits_str[12];
		int			sslbits;

		SSL_get_cipher_bits(conn->ssl, &sslbits);
		snprintf(sslbits_str, sizeof(sslbits_str), "%d", sslbits);
		return sslbits_str;
	}

	if (strcmp(attribute_name, "cipher") == 0)
		return SSL_get_cipher(conn->ssl);

	if (strcmp(attribute_name, "compression") == 0)
		return SSL_get_current_compression(conn->ssl) ? "on" : "off";

	if (strcmp(attribute_name, "protocol") == 0)
		return SSL_get_version(conn->ssl);

	return NULL;				/* unknown attribute */
}