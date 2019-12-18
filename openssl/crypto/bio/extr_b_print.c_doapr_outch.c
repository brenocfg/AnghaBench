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
 int /*<<< orphan*/  BIO_F_DOAPR_OUTCH ; 
 int /*<<< orphan*/  BIOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t BUFFER_INC ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 size_t INT_MAX ; 
 char* OPENSSL_malloc (size_t) ; 
 char* OPENSSL_realloc (char*,size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  ossl_assert (int) ; 

__attribute__((used)) static int
doapr_outch(char **sbuffer,
            char **buffer, size_t *currlen, size_t *maxlen, int c)
{
    /* If we haven't at least one buffer, someone has done a big booboo */
    if (!ossl_assert(*sbuffer != NULL || buffer != NULL))
        return 0;

    /* |currlen| must always be <= |*maxlen| */
    if (!ossl_assert(*currlen <= *maxlen))
        return 0;

    if (buffer && *currlen == *maxlen) {
        if (*maxlen > INT_MAX - BUFFER_INC)
            return 0;

        *maxlen += BUFFER_INC;
        if (*buffer == NULL) {
            if ((*buffer = OPENSSL_malloc(*maxlen)) == NULL) {
                BIOerr(BIO_F_DOAPR_OUTCH, ERR_R_MALLOC_FAILURE);
                return 0;
            }
            if (*currlen > 0) {
                if (!ossl_assert(*sbuffer != NULL))
                    return 0;
                memcpy(*buffer, *sbuffer, *currlen);
            }
            *sbuffer = NULL;
        } else {
            char *tmpbuf;
            tmpbuf = OPENSSL_realloc(*buffer, *maxlen);
            if (tmpbuf == NULL)
                return 0;
            *buffer = tmpbuf;
        }
    }

    if (*currlen < *maxlen) {
        if (*sbuffer)
            (*sbuffer)[(*currlen)++] = (char)c;
        else
            (*buffer)[(*currlen)++] = (char)c;
    }

    return 1;
}