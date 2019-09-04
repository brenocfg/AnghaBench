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
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_FLG_SECURE ; 
 TYPE_1__* BN_new () ; 

BIGNUM *BN_secure_new(void)
 {
     BIGNUM *ret = BN_new();
     if (ret != NULL)
         ret->flags |= BN_FLG_SECURE;
     return ret;
 }