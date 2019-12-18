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
 int /*<<< orphan*/  CRYPTO_F_CRYPTO_MEMDUP ; 
 void* CRYPTO_malloc (size_t,char const*,int) ; 
 int /*<<< orphan*/  CRYPTOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 size_t INT_MAX ; 
 void* memcpy (void*,void const*,size_t) ; 

void *CRYPTO_memdup(const void *data, size_t siz, const char* file, int line)
{
    void *ret;

    if (data == NULL || siz >= INT_MAX)
        return NULL;

    ret = CRYPTO_malloc(siz, file, line);
    if (ret == NULL) {
        CRYPTOerr(CRYPTO_F_CRYPTO_MEMDUP, ERR_R_MALLOC_FAILURE);
        return NULL;
    }
    return memcpy(ret, data, siz);
}