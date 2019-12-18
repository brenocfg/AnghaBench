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
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 char* OPENSSL_malloc (int) ; 
 char* OPENSSL_uni2asc (unsigned char const*,int) ; 
 int /*<<< orphan*/  PKCS12_F_OPENSSL_UNI2UTF8 ; 
 int /*<<< orphan*/  PKCS12err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bmp_to_utf8 (char*,unsigned char const*,int) ; 

char *OPENSSL_uni2utf8(const unsigned char *uni, int unilen)
{
    int asclen, i, j;
    char *asctmp;

    /* string must contain an even number of bytes */
    if (unilen & 1)
        return NULL;

    for (asclen = 0, i = 0; i < unilen; ) {
        j = bmp_to_utf8(NULL, uni+i, unilen-i);
        /*
         * falling back to OPENSSL_uni2asc makes lesser sense [than
         * falling back to OPENSSL_asc2uni in OPENSSL_utf82uni above],
         * it's done rather to maintain symmetry...
         */
        if (j < 0) return OPENSSL_uni2asc(uni, unilen);
        if (j == 4) i += 4;
        else        i += 2;
        asclen += j;
    }

    /* If no terminating zero allow for one */
    if (!unilen || (uni[unilen-2]||uni[unilen - 1]))
        asclen++;

    if ((asctmp = OPENSSL_malloc(asclen)) == NULL) {
        PKCS12err(PKCS12_F_OPENSSL_UNI2UTF8, ERR_R_MALLOC_FAILURE);
        return NULL;
    }

    /* re-run the loop emitting UTF-8 string */
    for (asclen = 0, i = 0; i < unilen; ) {
        j = bmp_to_utf8(asctmp+asclen, uni+i, unilen-i);
        if (j == 4) i += 4;
        else        i += 2;
        asclen += j;
    }

    /* If no terminating zero write one */
    if (!unilen || (uni[unilen-2]||uni[unilen - 1]))
        asctmp[asclen] = '\0';

    return asctmp;
}