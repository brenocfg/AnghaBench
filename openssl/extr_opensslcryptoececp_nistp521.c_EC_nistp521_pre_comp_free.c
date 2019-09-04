#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  references; } ;
typedef  TYPE_1__ NISTP521_PRE_COMP ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_DOWN_REF (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_lock_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/  REF_ASSERT_ISNT (int) ; 
 int /*<<< orphan*/  REF_PRINT_COUNT (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x ; 

void EC_nistp521_pre_comp_free(NISTP521_PRE_COMP *p)
{
    int i;

    if (p == NULL)
        return;

    CRYPTO_DOWN_REF(&p->references, &i, p->lock);
    REF_PRINT_COUNT("EC_nistp521", x);
    if (i > 0)
        return;
    REF_ASSERT_ISNT(i < 0);

    CRYPTO_THREAD_lock_free(p->lock);
    OPENSSL_free(p);
}