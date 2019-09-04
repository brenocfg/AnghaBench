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
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  BIO_puts (int /*<<< orphan*/ *,char*) ; 
 int SSL_get0_ec_point_formats (int /*<<< orphan*/ *,char const**) ; 
#define  TLSEXT_ECPOINTFORMAT_ansiX962_compressed_char2 130 
#define  TLSEXT_ECPOINTFORMAT_ansiX962_compressed_prime 129 
#define  TLSEXT_ECPOINTFORMAT_uncompressed 128 

int ssl_print_point_formats(BIO *out, SSL *s)
{
    int i, nformats;
    const char *pformats;
    nformats = SSL_get0_ec_point_formats(s, &pformats);
    if (nformats <= 0)
        return 1;
    BIO_puts(out, "Supported Elliptic Curve Point Formats: ");
    for (i = 0; i < nformats; i++, pformats++) {
        if (i)
            BIO_puts(out, ":");
        switch (*pformats) {
        case TLSEXT_ECPOINTFORMAT_uncompressed:
            BIO_puts(out, "uncompressed");
            break;

        case TLSEXT_ECPOINTFORMAT_ansiX962_compressed_prime:
            BIO_puts(out, "ansiX962_compressed_prime");
            break;

        case TLSEXT_ECPOINTFORMAT_ansiX962_compressed_char2:
            BIO_puts(out, "ansiX962_compressed_char2");
            break;

        default:
            BIO_printf(out, "unknown(%d)", (int)*pformats);
            break;

        }
    }
    BIO_puts(out, "\n");
    return 1;
}