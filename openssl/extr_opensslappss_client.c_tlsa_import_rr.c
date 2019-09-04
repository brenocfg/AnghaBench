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
typedef  unsigned char* uint8_t ;
struct tlsa_field {unsigned char** member_0; char* member_1; int /*<<< orphan*/  name; scalar_t__ var; int /*<<< orphan*/  (* parser ) (char const**,scalar_t__) ;int /*<<< orphan*/  const member_2; } ;
typedef  int /*<<< orphan*/  ossl_ssize_t ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*,...) ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char* const) ; 
 int SSL_dane_tlsa_add (int /*<<< orphan*/ *,unsigned char* const,unsigned char* const,unsigned char* const,unsigned char* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_err ; 
#define  checked_uint8 129 
#define  hexdecode 128 
 int /*<<< orphan*/  prog ; 
 int /*<<< orphan*/  stub1 (char const**,scalar_t__) ; 

__attribute__((used)) static int tlsa_import_rr(SSL *con, const char *rrdata)
{
    /* Not necessary to re-init these values; the "parsers" do that. */
    static uint8_t usage;
    static uint8_t selector;
    static uint8_t mtype;
    static unsigned char *data;
    static struct tlsa_field tlsa_fields[] = {
        { &usage, "usage", checked_uint8 },
        { &selector, "selector", checked_uint8 },
        { &mtype, "mtype", checked_uint8 },
        { &data, "data", hexdecode },
        { NULL, }
    };
    struct tlsa_field *f;
    int ret;
    const char *cp = rrdata;
    ossl_ssize_t len = 0;

    for (f = tlsa_fields; f->var; ++f) {
        /* Returns number of bytes produced, advances cp to next field */
        if ((len = f->parser(&cp, f->var)) <= 0) {
            BIO_printf(bio_err, "%s: warning: bad TLSA %s field in: %s\n",
                       prog, f->name, rrdata);
            return 0;
        }
    }
    /* The data field is last, so len is its length */
    ret = SSL_dane_tlsa_add(con, usage, selector, mtype, data, len);
    OPENSSL_free(data);

    if (ret == 0) {
        ERR_print_errors(bio_err);
        BIO_printf(bio_err, "%s: warning: unusable TLSA rrdata: %s\n",
                   prog, rrdata);
        return 0;
    }
    if (ret < 0) {
        ERR_print_errors(bio_err);
        BIO_printf(bio_err, "%s: warning: error loading TLSA rrdata: %s\n",
                   prog, rrdata);
        return 0;
    }
    return ret;
}