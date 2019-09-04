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
typedef  int /*<<< orphan*/  OPENSSL_LH_DOALL_FUNCARG ;
typedef  int /*<<< orphan*/  OPENSSL_LH_DOALL_FUNC ;
typedef  int /*<<< orphan*/  OPENSSL_LHASH ;

/* Variables and functions */
 int /*<<< orphan*/  doall_util_fn (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

void OPENSSL_LH_doall_arg(OPENSSL_LHASH *lh, OPENSSL_LH_DOALL_FUNCARG func, void *arg)
{
    doall_util_fn(lh, 1, (OPENSSL_LH_DOALL_FUNC)0, func, arg);
}