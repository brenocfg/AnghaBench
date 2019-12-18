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
struct TYPE_5__ {void* addr; } ;
typedef  TYPE_1__ MEM ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_MEM_CHECK_DISABLE ; 
 int /*<<< orphan*/  CRYPTO_MEM_CHECK_ENABLE ; 
 int /*<<< orphan*/  CRYPTO_mem_ctrl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 TYPE_1__* lh_MEM_delete (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  mem_check_on () ; 
 int /*<<< orphan*/ * mh ; 

void CRYPTO_mem_debug_free(void *addr, int before_p,
        const char *file, int line)
{
    MEM m, *mp;

    switch (before_p) {
    case 0:
        if (addr == NULL)
            break;

        if (mem_check_on() && (mh != NULL)) {
            CRYPTO_mem_ctrl(CRYPTO_MEM_CHECK_DISABLE);
            m.addr = addr;
            mp = lh_MEM_delete(mh, &m);
            OPENSSL_free(mp);
            CRYPTO_mem_ctrl(CRYPTO_MEM_CHECK_ENABLE);
        }
        break;
    case 1:
        break;
    }
}