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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  hugebuf ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int BIO_write (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 int /*<<< orphan*/  _dopr (char**,char**,size_t*,size_t*,int*,char const*,int /*<<< orphan*/ ) ; 

int BIO_vprintf(BIO *bio, const char *format, va_list args)
{
    int ret;
    size_t retlen;
    char hugebuf[1024 * 2];     /* Was previously 10k, which is unreasonable
                                 * in small-stack environments, like threads
                                 * or DOS programs. */
    char *hugebufp = hugebuf;
    size_t hugebufsize = sizeof(hugebuf);
    char *dynbuf = NULL;
    int ignored;

    dynbuf = NULL;
    if (!_dopr(&hugebufp, &dynbuf, &hugebufsize, &retlen, &ignored, format,
                args)) {
        OPENSSL_free(dynbuf);
        return -1;
    }
    if (dynbuf) {
        ret = BIO_write(bio, dynbuf, (int)retlen);
        OPENSSL_free(dynbuf);
    } else {
        ret = BIO_write(bio, hugebuf, (int)retlen);
    }
    return ret;
}