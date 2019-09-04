#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int pkey_id; int flags; } ;
typedef  TYPE_1__ EVP_PKEY_METHOD ;

/* Variables and functions */

void EVP_PKEY_meth_get0_info(int *ppkey_id, int *pflags,
                             const EVP_PKEY_METHOD *meth)
{
    if (ppkey_id)
        *ppkey_id = meth->pkey_id;
    if (pflags)
        *pflags = meth->flags;
}