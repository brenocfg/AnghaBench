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
 int ASN1_PCTX_FLAGS_SHOW_ABSENT ; 
 int ASN1_PCTX_FLAGS_SHOW_FIELD_STRUCT_NAME ; 
 int ASN1_PCTX_FLAGS_SHOW_SEQUENCE ; 
 int ASN1_PCTX_FLAGS_SHOW_SSOF ; 
 int ASN1_PCTX_FLAGS_SHOW_TYPE ; 
 int /*<<< orphan*/  ASN1_PCTX_new () ; 
 int /*<<< orphan*/  ASN1_PCTX_set_flags (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ASN1_PCTX_set_str_flags (int /*<<< orphan*/ ,int) ; 
 int ASN1_STRFLGS_DUMP_ALL ; 
 int ASN1_STRFLGS_SHOW_TYPE ; 
 int ASN1_STRFLGS_UTF8_CONVERT ; 
 int /*<<< orphan*/  CRYPTO_free_ex_index (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 int /*<<< orphan*/  FuzzerSetRand () ; 
 int /*<<< orphan*/  OPENSSL_INIT_LOAD_CRYPTO_STRINGS ; 
 int /*<<< orphan*/  OPENSSL_INIT_LOAD_SSL_STRINGS ; 
 int /*<<< orphan*/  OPENSSL_init_crypto (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_init_ssl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pctx ; 

int FuzzerInitialize(int *argc, char ***argv)
{
    pctx = ASN1_PCTX_new();
    ASN1_PCTX_set_flags(pctx, ASN1_PCTX_FLAGS_SHOW_ABSENT |
        ASN1_PCTX_FLAGS_SHOW_SEQUENCE | ASN1_PCTX_FLAGS_SHOW_SSOF |
        ASN1_PCTX_FLAGS_SHOW_TYPE | ASN1_PCTX_FLAGS_SHOW_FIELD_STRUCT_NAME);
    ASN1_PCTX_set_str_flags(pctx, ASN1_STRFLGS_UTF8_CONVERT |
        ASN1_STRFLGS_SHOW_TYPE | ASN1_STRFLGS_DUMP_ALL);

    OPENSSL_init_crypto(OPENSSL_INIT_LOAD_CRYPTO_STRINGS, NULL);
    OPENSSL_init_ssl(OPENSSL_INIT_LOAD_SSL_STRINGS, NULL);
    ERR_clear_error();
    CRYPTO_free_ex_index(0, -1);
    FuzzerSetRand();

    return 1;
}