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
struct TYPE_3__ {int /*<<< orphan*/  ex_data; } ;
typedef  TYPE_1__ DSA ;

/* Variables and functions */
 int CRYPTO_set_ex_data (int /*<<< orphan*/ *,int,void*) ; 

int DSA_set_ex_data(DSA *d, int idx, void *arg)
{
    return CRYPTO_set_ex_data(&d->ex_data, idx, arg);
}