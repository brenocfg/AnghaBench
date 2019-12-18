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
 unsigned char* OPENSSL_malloc (int) ; 
 int /*<<< orphan*/  PKCS12_F_OPENSSL_ASC2UNI ; 
 int /*<<< orphan*/  PKCS12err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 

unsigned char *OPENSSL_asc2uni(const char *asc, int asclen,
                               unsigned char **uni, int *unilen)
{
    int ulen, i;
    unsigned char *unitmp;

    if (asclen == -1)
        asclen = strlen(asc);
    ulen = asclen * 2 + 2;
    if ((unitmp = OPENSSL_malloc(ulen)) == NULL) {
        PKCS12err(PKCS12_F_OPENSSL_ASC2UNI, ERR_R_MALLOC_FAILURE);
        return NULL;
    }
    for (i = 0; i < ulen - 2; i += 2) {
        unitmp[i] = 0;
        unitmp[i + 1] = asc[i >> 1];
    }
    /* Make result double null terminated */
    unitmp[ulen - 2] = 0;
    unitmp[ulen - 1] = 0;
    if (unilen)
        *unilen = ulen;
    if (uni)
        *uni = unitmp;
    return unitmp;
}