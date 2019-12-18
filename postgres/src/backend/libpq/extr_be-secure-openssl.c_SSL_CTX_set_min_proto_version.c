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
typedef  int /*<<< orphan*/  SSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_CTX_set_options (int /*<<< orphan*/ *,int) ; 
 int SSL_OP_NO_SSLv2 ; 
 int SSL_OP_NO_SSLv3 ; 
 int SSL_OP_NO_TLSv1 ; 
 int SSL_OP_NO_TLSv1_1 ; 
 int SSL_OP_NO_TLSv1_2 ; 
 int TLS1_1_VERSION ; 
 int TLS1_2_VERSION ; 
 int TLS1_VERSION ; 

__attribute__((used)) static int
SSL_CTX_set_min_proto_version(SSL_CTX *ctx, int version)
{
	int			ssl_options = SSL_OP_NO_SSLv2 | SSL_OP_NO_SSLv3;

	if (version > TLS1_VERSION)
		ssl_options |= SSL_OP_NO_TLSv1;
	/*
	 * Some OpenSSL versions define TLS*_VERSION macros but not the
	 * corresponding SSL_OP_NO_* macro, so in those cases we have to return
	 * unsuccessfully here.
	 */
#ifdef TLS1_1_VERSION
	if (version > TLS1_1_VERSION)
	{
#ifdef SSL_OP_NO_TLSv1_1
		ssl_options |= SSL_OP_NO_TLSv1_1;
#else
		return 0;
#endif
	}
#endif
#ifdef TLS1_2_VERSION
	if (version > TLS1_2_VERSION)
	{
#ifdef SSL_OP_NO_TLSv1_2
		ssl_options |= SSL_OP_NO_TLSv1_2;
#else
		return 0;
#endif
	}
#endif

	SSL_CTX_set_options(ctx, ssl_options);

	return 1;					/* success */
}