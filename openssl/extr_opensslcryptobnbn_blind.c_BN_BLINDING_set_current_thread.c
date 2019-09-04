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
struct TYPE_3__ {int /*<<< orphan*/  tid; } ;
typedef  TYPE_1__ BN_BLINDING ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_get_current_id () ; 

void BN_BLINDING_set_current_thread(BN_BLINDING *b)
{
    b->tid = CRYPTO_THREAD_get_current_id();
}