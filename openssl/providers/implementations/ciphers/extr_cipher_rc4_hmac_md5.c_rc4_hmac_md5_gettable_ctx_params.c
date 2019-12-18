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
typedef  int /*<<< orphan*/  OSSL_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/  const* rc4_hmac_md5_known_gettable_ctx_params ; 

const OSSL_PARAM *rc4_hmac_md5_gettable_ctx_params(void)
{
    return rc4_hmac_md5_known_gettable_ctx_params;
}