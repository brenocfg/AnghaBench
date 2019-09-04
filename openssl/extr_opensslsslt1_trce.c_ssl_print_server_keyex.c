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
 int /*<<< orphan*/  BIO_indent (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  BIO_puts (int /*<<< orphan*/ *,char*) ; 
 unsigned char const EXPLICIT_CHAR2_CURVE_TYPE ; 
 unsigned char const EXPLICIT_PRIME_CURVE_TYPE ; 
 unsigned char const NAMED_CURVE_TYPE ; 
 int SSL_PSK ; 
#define  SSL_kDHE 134 
#define  SSL_kDHEPSK 133 
#define  SSL_kECDHE 132 
#define  SSL_kECDHEPSK 131 
#define  SSL_kPSK 130 
#define  SSL_kRSA 129 
#define  SSL_kRSAPSK 128 
 int ssl_get_keyex (char const**,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ssl_groups_tbl ; 
 int /*<<< orphan*/  ssl_print_hexbuf (int /*<<< orphan*/ *,int,char*,int,unsigned char const**,size_t*) ; 
 int /*<<< orphan*/  ssl_print_signature (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,unsigned char const**,size_t*) ; 
 int /*<<< orphan*/  ssl_trace_str (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ssl_print_server_keyex(BIO *bio, int indent, const SSL *ssl,
                                  const unsigned char *msg, size_t msglen)
{
    const char *algname;
    int id = ssl_get_keyex(&algname, ssl);

    BIO_indent(bio, indent, 80);
    BIO_printf(bio, "KeyExchangeAlgorithm=%s\n", algname);
    if (id & SSL_PSK) {
        if (!ssl_print_hexbuf(bio, indent + 2,
                              "psk_identity_hint", 2, &msg, &msglen))
            return 0;
    }
    switch (id) {
    case SSL_kRSA:

        if (!ssl_print_hexbuf(bio, indent + 2, "rsa_modulus", 2, &msg, &msglen))
            return 0;
        if (!ssl_print_hexbuf(bio, indent + 2, "rsa_exponent", 2,
                              &msg, &msglen))
            return 0;
        break;

    case SSL_kDHE:
    case SSL_kDHEPSK:
        if (!ssl_print_hexbuf(bio, indent + 2, "dh_p", 2, &msg, &msglen))
            return 0;
        if (!ssl_print_hexbuf(bio, indent + 2, "dh_g", 2, &msg, &msglen))
            return 0;
        if (!ssl_print_hexbuf(bio, indent + 2, "dh_Ys", 2, &msg, &msglen))
            return 0;
        break;

# ifndef OPENSSL_NO_EC
    case SSL_kECDHE:
    case SSL_kECDHEPSK:
        if (msglen < 1)
            return 0;
        BIO_indent(bio, indent + 2, 80);
        if (msg[0] == EXPLICIT_PRIME_CURVE_TYPE)
            BIO_puts(bio, "explicit_prime\n");
        else if (msg[0] == EXPLICIT_CHAR2_CURVE_TYPE)
            BIO_puts(bio, "explicit_char2\n");
        else if (msg[0] == NAMED_CURVE_TYPE) {
            int curve;
            if (msglen < 3)
                return 0;
            curve = (msg[1] << 8) | msg[2];
            BIO_printf(bio, "named_curve: %s (%d)\n",
                       ssl_trace_str(curve, ssl_groups_tbl), curve);
            msg += 3;
            msglen -= 3;
            if (!ssl_print_hexbuf(bio, indent + 2, "point", 1, &msg, &msglen))
                return 0;
        } else {
            BIO_printf(bio, "UNKNOWN CURVE PARAMETER TYPE %d\n", msg[0]);
            return 0;
        }
        break;
# endif

    case SSL_kPSK:
    case SSL_kRSAPSK:
        break;
    }
    if (!(id & SSL_PSK))
        ssl_print_signature(bio, indent, ssl, &msg, &msglen);
    return !msglen;
}