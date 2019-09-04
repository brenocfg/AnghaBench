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
struct TYPE_4__ {int /*<<< orphan*/  d; } ;
typedef  TYPE_1__ BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_FLG_SECURE ; 
 scalar_t__ BN_get_flags (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_secure_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bn_free_d(BIGNUM *a)
{
    if (BN_get_flags(a, BN_FLG_SECURE))
        OPENSSL_secure_free(a->d);
    else
        OPENSSL_free(a->d);
}