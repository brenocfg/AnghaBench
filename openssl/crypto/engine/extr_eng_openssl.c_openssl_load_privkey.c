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
typedef  int /*<<< orphan*/  UI_METHOD ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  ENGINE ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_file (char const*,char*) ; 
 int /*<<< orphan*/ * PEM_read_bio_PrivateKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static EVP_PKEY *openssl_load_privkey(ENGINE *eng, const char *key_id,
                                      UI_METHOD *ui_method,
                                      void *callback_data)
{
    BIO *in;
    EVP_PKEY *key;
    fprintf(stderr, "(TEST_ENG_OPENSSL_PKEY)Loading Private key %s\n",
            key_id);
    in = BIO_new_file(key_id, "r");
    if (!in)
        return NULL;
    key = PEM_read_bio_PrivateKey(in, NULL, 0, NULL);
    BIO_free(in);
    return key;
}