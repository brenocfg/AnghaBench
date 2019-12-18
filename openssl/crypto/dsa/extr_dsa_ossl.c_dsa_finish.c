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
struct TYPE_3__ {int /*<<< orphan*/  method_mont_p; } ;
typedef  TYPE_1__ DSA ;

/* Variables and functions */
 int /*<<< orphan*/  BN_MONT_CTX_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dsa_finish(DSA *dsa)
{
    BN_MONT_CTX_free(dsa->method_mont_p);
    return 1;
}