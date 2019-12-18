#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t num; int /*<<< orphan*/  array; int /*<<< orphan*/  array_siz; void* addr; } ;
typedef  TYPE_1__ MEM ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_MEM_CHECK_DISABLE ; 
 int /*<<< orphan*/  CRYPTO_MEM_CHECK_ENABLE ; 
 int /*<<< orphan*/  CRYPTO_mem_ctrl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_mem_debug_malloc (void*,size_t,int,char const*,int) ; 
 int /*<<< orphan*/  OSSL_NELEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  backtrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* lh_MEM_delete (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  lh_MEM_insert (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  mem_check_on () ; 
 int /*<<< orphan*/  mh ; 

void CRYPTO_mem_debug_realloc(void *addr1, void *addr2, size_t num,
                              int before_p, const char *file, int line)
{
    MEM m, *mp;

    switch (before_p) {
    case 0:
        break;
    case 1:
        if (addr2 == NULL)
            break;

        if (addr1 == NULL) {
            CRYPTO_mem_debug_malloc(addr2, num, 128 | before_p, file, line);
            break;
        }

        if (mem_check_on()) {
            CRYPTO_mem_ctrl(CRYPTO_MEM_CHECK_DISABLE);

            m.addr = addr1;
            mp = lh_MEM_delete(mh, &m);
            if (mp != NULL) {
                mp->addr = addr2;
                mp->num = num;
#ifndef OPENSSL_NO_CRYPTO_MDEBUG_BACKTRACE
                mp->array_siz = backtrace(mp->array, OSSL_NELEM(mp->array));
#endif
                (void)lh_MEM_insert(mh, mp);
            }

            CRYPTO_mem_ctrl(CRYPTO_MEM_CHECK_ENABLE);
        }
        break;
    }
    return;
}