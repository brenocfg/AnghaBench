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

int mbedtls_x509_test(int verbose,  char *ca_crt,  size_t ca_crt_len, char *cli_crt, size_t cli_crt_len)
{
#if defined(MBEDTLS_SHA1_C)
    int ret;
    uint32_t flags;
    mbedtls_x509_crt cacert;
    mbedtls_x509_crt clicert;

    if( verbose != 0 )
        os_printf( "  X.509 certificate load: " );

    mbedtls_x509_crt_init( &clicert );

    ret = mbedtls_x509_crt_parse( &clicert, (const unsigned char *) cli_crt,
                           cli_crt_len );
    if( ret != 0 )
    {
        if( verbose != 0 )
            os_printf( "failed\n" );

        return( ret );
    }

    mbedtls_x509_crt_init( &cacert );

    ret = mbedtls_x509_crt_parse( &cacert, (const unsigned char *) ca_crt,
                          ca_crt_len );
    if( ret != 0 )
    {
        if( verbose != 0 )
            os_printf( "failed\n" );

        return( ret );
    }

    if( verbose != 0 )
        os_printf( "passed\n  X.509 signature verify: ");

    ret = mbedtls_x509_crt_verify( &clicert, &cacert, NULL, NULL, &flags, NULL, NULL );
    if( ret != 0 )
    {
        if( verbose != 0 )
            os_printf( "failed\n" );

        return( ret );
    }

    if( verbose != 0 )
        os_printf( "passed\n\n");

    mbedtls_x509_crt_free( &cacert  );
    mbedtls_x509_crt_free( &clicert );

    return( 0 );
#else
    ((void) verbose);
    return( 0 );
#endif /* MBEDTLS_CERTS_C && MBEDTLS_SHA1_C */
}