#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {unsigned char* data; int /*<<< orphan*/  rec_version; int /*<<< orphan*/  type; } ;
struct TYPE_19__ {TYPE_3__* new_cipher; } ;
struct TYPE_20__ {TYPE_1__ tmp; } ;
struct TYPE_21__ {struct TYPE_21__* enc_read_ctx; struct TYPE_21__* enc_write_ctx; int /*<<< orphan*/  read_iv; int /*<<< orphan*/  write_iv; int /*<<< orphan*/  rlayer; TYPE_2__ s3; } ;
typedef  TYPE_3__ SSL_CTX ;
typedef  TYPE_4__ SSL3_RECORD ;
typedef  TYPE_3__ SSL ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;

/* Variables and functions */
 void* EVP_CIPHER_CTX_new () ; 
 size_t EVP_CIPHER_iv_length (int /*<<< orphan*/  const*) ; 
 scalar_t__ EVP_CipherInit_ex (TYPE_3__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * EVP_aes_128_gcm () ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 size_t OSSL_NELEM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RECORD_LAYER_get_read_sequence (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RECORD_LAYER_get_write_sequence (int /*<<< orphan*/ *) ; 
 size_t SEQ_NUM_SIZE ; 
 int /*<<< orphan*/  SSL3_RT_APPLICATION_DATA ; 
 TYPE_3__* SSL_CIPHER_find (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_free (TYPE_3__*) ; 
 TYPE_3__* SSL_CTX_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_free (TYPE_3__*) ; 
 TYPE_3__* SSL_new (TYPE_3__*) ; 
 int /*<<< orphan*/  TEST_error (char*) ; 
 int /*<<< orphan*/  TEST_info (char*,...) ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEST_note (char*,size_t) ; 
 int /*<<< orphan*/  TEST_ptr (TYPE_3__*) ; 
 int /*<<< orphan*/  TEST_size_t_eq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLS13_AES_128_GCM_SHA256_BYTES ; 
 int /*<<< orphan*/  TLS1_2_VERSION ; 
 int /*<<< orphan*/  TLS_method () ; 
 int /*<<< orphan*/  load_record (TYPE_4__*,int /*<<< orphan*/ *,unsigned char**,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/ * refdata ; 
 int /*<<< orphan*/  test_record (TYPE_4__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tls13_enc (TYPE_3__*,TYPE_4__*,int,int) ; 

__attribute__((used)) static int test_tls13_encryption(void)
{
    SSL_CTX *ctx = NULL;
    SSL *s = NULL;
    SSL3_RECORD rec;
    unsigned char *key = NULL, *iv = NULL, *seq = NULL;
    const EVP_CIPHER *ciph = EVP_aes_128_gcm();
    int ret = 0;
    size_t ivlen, ctr;

    /*
     * Encrypted TLSv1.3 records always have an outer content type of
     * application data, and a record version of TLSv1.2.
     */
    rec.data = NULL;
    rec.type = SSL3_RT_APPLICATION_DATA;
    rec.rec_version = TLS1_2_VERSION;

    ctx = SSL_CTX_new(TLS_method());
    if (!TEST_ptr(ctx)) {
        TEST_info("Failed creating SSL_CTX");
        goto err;
    }

    s = SSL_new(ctx);
    if (!TEST_ptr(s)) {
        TEST_info("Failed creating SSL");
        goto err;
    }

    s->enc_read_ctx = EVP_CIPHER_CTX_new();
    if (!TEST_ptr(s->enc_read_ctx))
        goto err;

    s->enc_write_ctx = EVP_CIPHER_CTX_new();
    if (!TEST_ptr(s->enc_write_ctx))
        goto err;

    s->s3.tmp.new_cipher = SSL_CIPHER_find(s, TLS13_AES_128_GCM_SHA256_BYTES);
    if (!TEST_ptr(s->s3.tmp.new_cipher)) {
        TEST_info("Failed to find cipher");
        goto err;
    }

    for (ctr = 0; ctr < OSSL_NELEM(refdata); ctr++) {
        /* Load the record */
        ivlen = EVP_CIPHER_iv_length(ciph);
        if (!load_record(&rec, &refdata[ctr], &key, s->read_iv, ivlen,
                         RECORD_LAYER_get_read_sequence(&s->rlayer))) {
            TEST_error("Failed loading key into EVP_CIPHER_CTX");
            goto err;
        }

        /* Set up the read/write sequences */
        memcpy(RECORD_LAYER_get_write_sequence(&s->rlayer),
               RECORD_LAYER_get_read_sequence(&s->rlayer), SEQ_NUM_SIZE);
        memcpy(s->write_iv, s->read_iv, ivlen);

        /* Load the key into the EVP_CIPHER_CTXs */
        if (EVP_CipherInit_ex(s->enc_write_ctx, ciph, NULL, key, NULL, 1) <= 0
                || EVP_CipherInit_ex(s->enc_read_ctx, ciph, NULL, key, NULL, 0)
                   <= 0) {
            TEST_error("Failed loading key into EVP_CIPHER_CTX\n");
            goto err;
        }

        /* Encrypt it */
        if (!TEST_size_t_eq(tls13_enc(s, &rec, 1, 1), 1)) {
            TEST_info("Failed to encrypt record %zu", ctr);
            goto err;
        }
        if (!TEST_true(test_record(&rec, &refdata[ctr], 1))) {
            TEST_info("Record %zu encryption test failed", ctr);
            goto err;
        }

        /* Decrypt it */
        if (!TEST_int_eq(tls13_enc(s, &rec, 1, 0), 1)) {
            TEST_info("Failed to decrypt record %zu", ctr);
            goto err;
        }
        if (!TEST_true(test_record(&rec, &refdata[ctr], 0))) {
            TEST_info("Record %zu decryption test failed", ctr);
            goto err;
        }

        OPENSSL_free(rec.data);
        OPENSSL_free(key);
        OPENSSL_free(iv);
        OPENSSL_free(seq);
        rec.data = NULL;
        key = NULL;
        iv = NULL;
        seq = NULL;
    }

    TEST_note("PASS: %zu records tested", ctr);
    ret = 1;

 err:
    OPENSSL_free(rec.data);
    OPENSSL_free(key);
    OPENSSL_free(iv);
    OPENSSL_free(seq);
    SSL_free(s);
    SSL_CTX_free(ctx);
    return ret;
}