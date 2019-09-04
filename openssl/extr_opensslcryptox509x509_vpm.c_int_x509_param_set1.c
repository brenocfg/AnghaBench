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
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 void* OPENSSL_memdup (char const*,size_t) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int int_x509_param_set1(char **pdest, size_t *pdestlen,
                               const char *src, size_t srclen)
{
    void *tmp;
    if (src) {
        if (srclen == 0)
            srclen = strlen(src);

        tmp = OPENSSL_memdup(src, srclen);
        if (tmp == NULL)
            return 0;
    } else {
        tmp = NULL;
        srclen = 0;
    }
    OPENSSL_free(*pdest);
    *pdest = tmp;
    if (pdestlen != NULL)
        *pdestlen = srclen;
    return 1;
}