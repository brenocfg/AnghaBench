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
 int /*<<< orphan*/  const* chacha20_poly1305_known_gettable_ctx_params ; 

__attribute__((used)) static const OSSL_PARAM *chacha20_poly1305_gettable_ctx_params(void)
{
    return chacha20_poly1305_known_gettable_ctx_params;
}