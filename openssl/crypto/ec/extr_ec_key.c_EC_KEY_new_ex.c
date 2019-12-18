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
typedef  int /*<<< orphan*/  OPENSSL_CTX ;
typedef  int /*<<< orphan*/  EC_KEY ;

/* Variables and functions */
 int /*<<< orphan*/ * ec_key_new_method_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

EC_KEY *EC_KEY_new_ex(OPENSSL_CTX *ctx)
{
    return ec_key_new_method_int(ctx, NULL);
}