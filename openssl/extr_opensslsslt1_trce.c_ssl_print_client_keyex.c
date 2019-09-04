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
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  SSL3_VERSION ; 
 int SSL_PSK ; 
#define  SSL_kDHE 133 
#define  SSL_kDHEPSK 132 
#define  SSL_kECDHE 131 
#define  SSL_kECDHEPSK 130 
#define  SSL_kRSA 129 
#define  SSL_kRSAPSK 128 
 int /*<<< orphan*/  TLS1_get_version (int /*<<< orphan*/  const*) ; 
 int ssl_get_keyex (char const**,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ssl_print_hex (int /*<<< orphan*/ *,int,char*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  ssl_print_hexbuf (int /*<<< orphan*/ *,int,char*,int,unsigned char const**,size_t*) ; 

__attribute__((used)) static int ssl_print_client_keyex(BIO *bio, int indent, const SSL *ssl,
                                  const unsigned char *msg, size_t msglen)
{
    const char *algname;
    int id = ssl_get_keyex(&algname, ssl);

    BIO_indent(bio, indent, 80);
    BIO_printf(bio, "KeyExchangeAlgorithm=%s\n", algname);
    if (id & SSL_PSK) {
        if (!ssl_print_hexbuf(bio, indent + 2,
                              "psk_identity", 2, &msg, &msglen))
            return 0;
    }
    switch (id) {

    case SSL_kRSA:
    case SSL_kRSAPSK:
        if (TLS1_get_version(ssl) == SSL3_VERSION) {
            ssl_print_hex(bio, indent + 2,
                          "EncryptedPreMasterSecret", msg, msglen);
        } else {
            if (!ssl_print_hexbuf(bio, indent + 2,
                                  "EncryptedPreMasterSecret", 2, &msg, &msglen))
                return 0;
        }
        break;

    case SSL_kDHE:
    case SSL_kDHEPSK:
        if (!ssl_print_hexbuf(bio, indent + 2, "dh_Yc", 2, &msg, &msglen))
            return 0;
        break;

    case SSL_kECDHE:
    case SSL_kECDHEPSK:
        if (!ssl_print_hexbuf(bio, indent + 2, "ecdh_Yc", 1, &msg, &msglen))
            return 0;
        break;

    }

    return !msglen;
}