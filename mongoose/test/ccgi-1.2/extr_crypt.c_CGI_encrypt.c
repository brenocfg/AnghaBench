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
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;

/* Variables and functions */
 char* CGI_encode_base64 (unsigned char*,int) ; 
 int DIGEST_SIZE ; 
 int /*<<< orphan*/  EVP_BytesToKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,unsigned char*,int /*<<< orphan*/ ,int,unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  EVP_EncryptFinal (int /*<<< orphan*/ *,unsigned char*,int*) ; 
 int /*<<< orphan*/  EVP_EncryptInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  EVP_EncryptUpdate (int /*<<< orphan*/ *,unsigned char*,int*,void const*,int) ; 
 int EVP_MAX_BLOCK_LENGTH ; 
 int EVP_MAX_IV_LENGTH ; 
 int EVP_MAX_KEY_LENGTH ; 
 int /*<<< orphan*/  EVP_aes_256_cbc () ; 
 int /*<<< orphan*/  EVP_sha1 () ; 
 int SALT_SIZE ; 
 int /*<<< orphan*/  digest (void const*,int,char const*,unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int /*<<< orphan*/  init_salt (unsigned char*) ; 
 unsigned char* malloc (int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

char *
CGI_encrypt(const void *p, int len, const char *password) {
    EVP_CIPHER_CTX ctx;
    unsigned char md[DIGEST_SIZE];
    unsigned char iv[EVP_MAX_IV_LENGTH];
    unsigned char key[EVP_MAX_KEY_LENGTH];
    unsigned char *out;
    char *b64;
    int offset, rlen;

    if (p == 0 || len <= 0 || password == 0 || *password == 0) {
        return 0;
    }
    out = malloc(SALT_SIZE + DIGEST_SIZE + len + EVP_MAX_BLOCK_LENGTH);
    init_salt(out);
    digest(p, len, password, out, md);
    EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha1(), out,
        (unsigned char *) password, strlen(password), 1, key, iv);
    EVP_EncryptInit(&ctx, EVP_aes_256_cbc(), key, iv);
    offset = SALT_SIZE;
    EVP_EncryptUpdate(&ctx, out + offset, &rlen, md, DIGEST_SIZE);
    offset += rlen;
    EVP_EncryptUpdate(&ctx, out + offset, &rlen, p, len);
    offset += rlen;
    EVP_EncryptFinal(&ctx, out + offset, &rlen);
    b64 = CGI_encode_base64(out, offset + rlen);
    free(out);
    return b64;
}