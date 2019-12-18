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
struct TYPE_4__ {int /*<<< orphan*/  provctx; } ;
typedef  int /*<<< orphan*/  OSSL_thread_stop_handler_fn ;
typedef  TYPE_1__ OSSL_PROVIDER ;

/* Variables and functions */
 int ossl_init_thread_start (TYPE_1__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int core_thread_start(const OSSL_PROVIDER *prov,
                             OSSL_thread_stop_handler_fn handfn)
{
    return ossl_init_thread_start(prov, prov->provctx, handfn);
}