#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * hostname; int /*<<< orphan*/ * session; int /*<<< orphan*/ * session_negotiate; int /*<<< orphan*/ * transform_negotiate; int /*<<< orphan*/ * handshake; } ;
typedef  TYPE_1__ mbedtls_ssl_context ;

/* Variables and functions */
 int /*<<< orphan*/  lwIP_ASSERT (TYPE_1__*) ; 
 int /*<<< orphan*/  mbedtls_ssl_handshake_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_ssl_session_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_ssl_transform_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_zeroize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mbedtls_handshake_succ(mbedtls_ssl_context *ssl)
{
	lwIP_ASSERT(ssl);
	if( ssl->handshake )
    {
        mbedtls_ssl_handshake_free( ssl->handshake );
        mbedtls_ssl_transform_free( ssl->transform_negotiate );
        mbedtls_ssl_session_free( ssl->session_negotiate );

        os_free( ssl->handshake );
        os_free( ssl->transform_negotiate );
        os_free( ssl->session_negotiate );
		ssl->handshake = NULL;
		ssl->transform_negotiate = NULL;
		ssl->session_negotiate = NULL;
    }

    if( ssl->session )
    {
        mbedtls_ssl_session_free( ssl->session );
        os_free( ssl->session );
		ssl->session = NULL;
    }

#if defined(MBEDTLS_X509_CRT_PARSE_C)
    if( ssl->hostname != NULL )
    {
        mbedtls_zeroize( ssl->hostname, os_strlen( ssl->hostname ) );
        os_free( ssl->hostname );
		ssl->hostname = NULL;
    }
#endif
}