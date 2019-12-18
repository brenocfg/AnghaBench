#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  php_stream ;
struct TYPE_3__ {unsigned char* signature; int sig_flags; int /*<<< orphan*/  sig_len; int /*<<< orphan*/  fname; } ;
typedef  TYPE_1__ phar_archive_data ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  PHP_SHA512_CTX ;
typedef  int /*<<< orphan*/  PHP_SHA256_CTX ;
typedef  int /*<<< orphan*/  PHP_SHA1_CTX ;
typedef  int /*<<< orphan*/  PHP_MD5_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_mem_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_create () ; 
 int /*<<< orphan*/  EVP_MD_CTX_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 unsigned int EVP_PKEY_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_SignFinal (int /*<<< orphan*/ *,unsigned char*,unsigned int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_SignInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_SignUpdate (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  EVP_sha1 () ; 
 int FAILURE ; 
 int /*<<< orphan*/ * PEM_read_bio_PrivateKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PHAR_G (int /*<<< orphan*/ ) ; 
#define  PHAR_SIG_MD5 132 
#define  PHAR_SIG_OPENSSL 131 
#define  PHAR_SIG_SHA1 130 
#define  PHAR_SIG_SHA256 129 
#define  PHAR_SIG_SHA512 128 
 int /*<<< orphan*/  PHP_MD5Final (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PHP_MD5Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PHP_MD5Update (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  PHP_SHA1Final (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PHP_SHA1Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PHP_SHA1Update (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  PHP_SHA256Final (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PHP_SHA256Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PHP_SHA256Update (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  PHP_SHA512Final (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PHP_SHA512Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PHP_SHA512Update (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  SEEK_END ; 
 int SUCCESS ; 
 int /*<<< orphan*/  efree (unsigned char*) ; 
 unsigned char* emalloc (unsigned int) ; 
 char* estrndup (char*,int) ; 
 int /*<<< orphan*/  openssl_privatekey ; 
 int /*<<< orphan*/  openssl_privatekey_len ; 
 int phar_call_openssl_signverify (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**,size_t*) ; 
 int /*<<< orphan*/  phar_hex_str (char const*,size_t,unsigned char**) ; 
 size_t php_stream_read (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  php_stream_rewind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_stream_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_stream_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spprintf (char**,int /*<<< orphan*/ ,char*,...) ; 

int phar_create_signature(phar_archive_data *phar, php_stream *fp, char **signature, size_t *signature_length, char **error) /* {{{ */
{
	unsigned char buf[1024];
	size_t sig_len;

	php_stream_rewind(fp);

	if (phar->signature) {
		efree(phar->signature);
		phar->signature = NULL;
	}

	switch(phar->sig_flags) {
		case PHAR_SIG_SHA512: {
			unsigned char digest[64];
			PHP_SHA512_CTX context;

			PHP_SHA512Init(&context);

			while ((sig_len = php_stream_read(fp, (char*)buf, sizeof(buf))) > 0) {
				PHP_SHA512Update(&context, buf, sig_len);
			}

			PHP_SHA512Final(digest, &context);
			*signature = estrndup((char *) digest, 64);
			*signature_length = 64;
			break;
		}
		case PHAR_SIG_SHA256: {
			unsigned char digest[32];
			PHP_SHA256_CTX  context;

			PHP_SHA256Init(&context);

			while ((sig_len = php_stream_read(fp, (char*)buf, sizeof(buf))) > 0) {
				PHP_SHA256Update(&context, buf, sig_len);
			}

			PHP_SHA256Final(digest, &context);
			*signature = estrndup((char *) digest, 32);
			*signature_length = 32;
			break;
		}
		case PHAR_SIG_OPENSSL: {
			unsigned char *sigbuf;
#ifdef PHAR_HAVE_OPENSSL
			unsigned int siglen;
			BIO *in;
			EVP_PKEY *key;
			EVP_MD_CTX *md_ctx;

			in = BIO_new_mem_buf(PHAR_G(openssl_privatekey), PHAR_G(openssl_privatekey_len));

			if (in == NULL) {
				if (error) {
					spprintf(error, 0, "unable to write to phar \"%s\" with requested openssl signature", phar->fname);
				}
				return FAILURE;
			}

			key = PEM_read_bio_PrivateKey(in, NULL,NULL, "");
			BIO_free(in);

			if (!key) {
				if (error) {
					spprintf(error, 0, "unable to process private key");
				}
				return FAILURE;
			}

			md_ctx = EVP_MD_CTX_create();

			siglen = EVP_PKEY_size(key);
			sigbuf = emalloc(siglen + 1);

			if (!EVP_SignInit(md_ctx, EVP_sha1())) {
				EVP_PKEY_free(key);
				efree(sigbuf);
				if (error) {
					spprintf(error, 0, "unable to initialize openssl signature for phar \"%s\"", phar->fname);
				}
				return FAILURE;
			}

			while ((sig_len = php_stream_read(fp, (char*)buf, sizeof(buf))) > 0) {
				if (!EVP_SignUpdate(md_ctx, buf, sig_len)) {
					EVP_PKEY_free(key);
					efree(sigbuf);
					if (error) {
						spprintf(error, 0, "unable to update the openssl signature for phar \"%s\"", phar->fname);
					}
					return FAILURE;
				}
			}

			if (!EVP_SignFinal (md_ctx, sigbuf, &siglen, key)) {
				EVP_PKEY_free(key);
				efree(sigbuf);
				if (error) {
					spprintf(error, 0, "unable to write phar \"%s\" with requested openssl signature", phar->fname);
				}
				return FAILURE;
			}

			sigbuf[siglen] = '\0';
			EVP_PKEY_free(key);
			EVP_MD_CTX_destroy(md_ctx);
#else
			size_t siglen;
			sigbuf = NULL;
			siglen = 0;
			php_stream_seek(fp, 0, SEEK_END);

			if (FAILURE == phar_call_openssl_signverify(1, fp, php_stream_tell(fp), PHAR_G(openssl_privatekey), PHAR_G(openssl_privatekey_len), (char **)&sigbuf, &siglen)) {
				if (error) {
					spprintf(error, 0, "unable to write phar \"%s\" with requested openssl signature", phar->fname);
				}
				return FAILURE;
			}
#endif
			*signature = (char *) sigbuf;
			*signature_length = siglen;
		}
		break;
		default:
			phar->sig_flags = PHAR_SIG_SHA1;
		case PHAR_SIG_SHA1: {
			unsigned char digest[20];
			PHP_SHA1_CTX  context;

			PHP_SHA1Init(&context);

			while ((sig_len = php_stream_read(fp, (char*)buf, sizeof(buf))) > 0) {
				PHP_SHA1Update(&context, buf, sig_len);
			}

			PHP_SHA1Final(digest, &context);
			*signature = estrndup((char *) digest, 20);
			*signature_length = 20;
			break;
		}
		case PHAR_SIG_MD5: {
			unsigned char digest[16];
			PHP_MD5_CTX   context;

			PHP_MD5Init(&context);

			while ((sig_len = php_stream_read(fp, (char*)buf, sizeof(buf))) > 0) {
				PHP_MD5Update(&context, buf, sig_len);
			}

			PHP_MD5Final(digest, &context);
			*signature = estrndup((char *) digest, 16);
			*signature_length = 16;
			break;
		}
	}

	phar->sig_len = phar_hex_str((const char *)*signature, *signature_length, &phar->signature);
	return SUCCESS;
}