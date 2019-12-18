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
struct TYPE_3__ {int /*<<< orphan*/ * ctx; } ;
typedef  int /*<<< orphan*/  OPENSSL_CTX ;
typedef  TYPE_1__ CRYPTO_EX_DATA ;

/* Variables and functions */

OPENSSL_CTX *crypto_ex_data_get_openssl_ctx(const CRYPTO_EX_DATA *ad)
{
    return ad->ctx;
}