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
typedef  scalar_t__ passwd_modes ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,...) ; 
 char* DES_crypt (char*,char*) ; 
 scalar_t__ RAND_bytes (unsigned char*,size_t) ; 
 char* app_malloc (size_t,char*) ; 
 int /*<<< orphan*/  ascii2ebcdic (char*,char*,size_t) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bio_err ; 
 char* cov_2char ; 
 char* md5crypt (char*,char*,char*) ; 
 scalar_t__ passwd_aixmd5 ; 
 scalar_t__ passwd_apr1 ; 
 scalar_t__ passwd_crypt ; 
 scalar_t__ passwd_md5 ; 
 scalar_t__ passwd_sha256 ; 
 scalar_t__ passwd_sha512 ; 
 char* shacrypt (char*,char*,char*) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static int do_passwd(int passed_salt, char **salt_p, char **salt_malloc_p,
                     char *passwd, BIO *out, int quiet, int table,
                     int reverse, size_t pw_maxlen, passwd_modes mode)
{
    char *hash = NULL;

    assert(salt_p != NULL);
    assert(salt_malloc_p != NULL);

    /* first make sure we have a salt */
    if (!passed_salt) {
        size_t saltlen = 0;
        size_t i;

#ifndef OPENSSL_NO_DES
        if (mode == passwd_crypt)
            saltlen = 2;
#endif                         /* !OPENSSL_NO_DES */

        if (mode == passwd_md5 || mode == passwd_apr1 || mode == passwd_aixmd5)
            saltlen = 8;

        if (mode == passwd_sha256 || mode == passwd_sha512)
            saltlen = 16;

        assert(saltlen != 0);

        if (*salt_malloc_p == NULL)
            *salt_p = *salt_malloc_p = app_malloc(saltlen + 1, "salt buffer");
        if (RAND_bytes((unsigned char *)*salt_p, saltlen) <= 0)
            goto end;

        for (i = 0; i < saltlen; i++)
            (*salt_p)[i] = cov_2char[(*salt_p)[i] & 0x3f]; /* 6 bits */
        (*salt_p)[i] = 0;
# ifdef CHARSET_EBCDIC
        /* The password encryption funtion will convert back to ASCII */
        ascii2ebcdic(*salt_p, *salt_p, saltlen);
# endif
    }

    assert(*salt_p != NULL);

    /* truncate password if necessary */
    if ((strlen(passwd) > pw_maxlen)) {
        if (!quiet)
            /*
             * XXX: really we should know how to print a size_t, not cast it
             */
            BIO_printf(bio_err,
                       "Warning: truncating password to %u characters\n",
                       (unsigned)pw_maxlen);
        passwd[pw_maxlen] = 0;
    }
    assert(strlen(passwd) <= pw_maxlen);

    /* now compute password hash */
#ifndef OPENSSL_NO_DES
    if (mode == passwd_crypt)
        hash = DES_crypt(passwd, *salt_p);
#endif
    if (mode == passwd_md5 || mode == passwd_apr1)
        hash = md5crypt(passwd, (mode == passwd_md5 ? "1" : "apr1"), *salt_p);
    if (mode == passwd_aixmd5)
        hash = md5crypt(passwd, "", *salt_p);
    if (mode == passwd_sha256 || mode == passwd_sha512)
        hash = shacrypt(passwd, (mode == passwd_sha256 ? "5" : "6"), *salt_p);
    assert(hash != NULL);

    if (table && !reverse)
        BIO_printf(out, "%s\t%s\n", passwd, hash);
    else if (table && reverse)
        BIO_printf(out, "%s\t%s\n", hash, passwd);
    else
        BIO_printf(out, "%s\n", hash);
    return 1;

 end:
    return 0;
}