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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  iv ;
typedef  int /*<<< orphan*/  HMAC_CTX ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_write (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_CIPHER_CTX_new () ; 
 int /*<<< orphan*/  EVP_Cipher (int /*<<< orphan*/ *,unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  EVP_CipherInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  EVP_aes_128_cbc () ; 
 int /*<<< orphan*/  EVP_sha1 () ; 
 int /*<<< orphan*/  HMAC_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * HMAC_CTX_new () ; 
 int /*<<< orphan*/  HMAC_Final (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HMAC_Init_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HMAC_Update (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (size_t) ; 
 int /*<<< orphan*/  RAND_bytes (unsigned char*,int) ; 
 size_t SHA_DIGEST_LENGTH ; 
 int /*<<< orphan*/  enc_key ; 
 int /*<<< orphan*/  mac_key ; 
 int /*<<< orphan*/  memcpy (unsigned char*,void const*,size_t) ; 

__attribute__((used)) static int send_record(BIO *rbio, unsigned char type, uint64_t seqnr,
                       const void *msg, size_t len)
{
    /* Note that the order of the record header fields on the wire,
     * and in the HMAC, is different. So we just keep them in separate
     * variables and handle them individually. */
    static unsigned char epoch[2] = { 0x00, 0x01 };
    static unsigned char seq[6] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    static unsigned char ver[2] = { 0x01, 0x00 }; /* DTLS1_BAD_VER */
    unsigned char lenbytes[2];
    HMAC_CTX *ctx;
    EVP_CIPHER_CTX *enc_ctx;
    unsigned char iv[16];
    unsigned char pad;
    unsigned char *enc;

    seq[0] = (seqnr >> 40) & 0xff;
    seq[1] = (seqnr >> 32) & 0xff;
    seq[2] = (seqnr >> 24) & 0xff;
    seq[3] = (seqnr >> 16) & 0xff;
    seq[4] = (seqnr >> 8) & 0xff;
    seq[5] = seqnr & 0xff;

    pad = 15 - ((len + SHA_DIGEST_LENGTH) % 16);
    enc = OPENSSL_malloc(len + SHA_DIGEST_LENGTH + 1 + pad);
    if (enc == NULL)
        return 0;

    /* Copy record to encryption buffer */
    memcpy(enc, msg, len);

    /* Append HMAC to data */
    ctx = HMAC_CTX_new();
    HMAC_Init_ex(ctx, mac_key, 20, EVP_sha1(), NULL);
    HMAC_Update(ctx, epoch, 2);
    HMAC_Update(ctx, seq, 6);
    HMAC_Update(ctx, &type, 1);
    HMAC_Update(ctx, ver, 2); /* Version */
    lenbytes[0] = (unsigned char)(len >> 8);
    lenbytes[1] = (unsigned char)(len);
    HMAC_Update(ctx, lenbytes, 2); /* Length */
    HMAC_Update(ctx, enc, len); /* Finally the data itself */
    HMAC_Final(ctx, enc + len, NULL);
    HMAC_CTX_free(ctx);

    /* Append padding bytes */
    len += SHA_DIGEST_LENGTH;
    do {
        enc[len++] = pad;
    } while (len % 16);

    /* Generate IV, and encrypt */
    RAND_bytes(iv, sizeof(iv));
    enc_ctx = EVP_CIPHER_CTX_new();
    EVP_CipherInit_ex(enc_ctx, EVP_aes_128_cbc(), NULL, enc_key, iv, 1);
    EVP_Cipher(enc_ctx, enc, enc, len);
    EVP_CIPHER_CTX_free(enc_ctx);

    /* Finally write header (from fragmented variables), IV and encrypted record */
    BIO_write(rbio, &type, 1);
    BIO_write(rbio, ver, 2);
    BIO_write(rbio, epoch, 2);
    BIO_write(rbio, seq, 6);
    lenbytes[0] = (unsigned char)((len + sizeof(iv)) >> 8);
    lenbytes[1] = (unsigned char)(len + sizeof(iv));
    BIO_write(rbio, lenbytes, 2);

    BIO_write(rbio, iv, sizeof(iv));
    BIO_write(rbio, enc, len);

    OPENSSL_free(enc);
    return 1;
}