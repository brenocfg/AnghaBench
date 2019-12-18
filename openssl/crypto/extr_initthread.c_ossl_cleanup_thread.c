#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int sane; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_cleanup_local (int /*<<< orphan*/ *) ; 
 TYPE_1__ destructor_key ; 
 int /*<<< orphan*/  init_thread_deregister (int /*<<< orphan*/ *,int) ; 

void ossl_cleanup_thread(void)
{
    init_thread_deregister(NULL, 1);
    CRYPTO_THREAD_cleanup_local(&destructor_key.value);
    destructor_key.sane = -1;
}