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

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b1 ; 
 int /*<<< orphan*/  b2 ; 
 int /*<<< orphan*/  b3 ; 
 int /*<<< orphan*/  b4 ; 
 int /*<<< orphan*/  b5 ; 
 int /*<<< orphan*/  ctx ; 

void FuzzerCleanup(void)
{
    BN_free(b1);
    BN_free(b2);
    BN_free(b3);
    BN_free(b4);
    BN_free(b5);
    BN_CTX_free(ctx);
}