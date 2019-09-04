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
typedef  TYPE_1__ EC_PRE_COMP ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_UP_REF (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 

EC_PRE_COMP *EC_ec_pre_comp_dup(EC_PRE_COMP *pre)
{
    int i;
    if (pre != NULL)
        CRYPTO_UP_REF(&pre->references, &i, pre->lock);
    return pre;
}