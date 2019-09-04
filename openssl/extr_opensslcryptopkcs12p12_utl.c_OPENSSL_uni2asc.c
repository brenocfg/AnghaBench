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
 int /*<<< orphan*/  PKCS12_F_OPENSSL_UNI2ASC ; 
 int /*<<< orphan*/  PKCS12err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

char *OPENSSL_uni2asc(const unsigned char *uni, int unilen)
{
    int asclen, i;
    char *asctmp;
    /* string must contain an even number of bytes */
    if (unilen & 1)
        return NULL;
    asclen = unilen / 2;
    /* If no terminating zero allow for one */
    if (!unilen || uni[unilen - 1])
        asclen++;
    uni++;
    if ((asctmp = OPENSSL_malloc(asclen)) == NULL) {
        PKCS12err(PKCS12_F_OPENSSL_UNI2ASC, ERR_R_MALLOC_FAILURE);
        return NULL;
    }
    for (i = 0; i < unilen; i += 2)
        asctmp[i >> 1] = uni[i];
    asctmp[asclen - 1] = 0;
    return asctmp;
}