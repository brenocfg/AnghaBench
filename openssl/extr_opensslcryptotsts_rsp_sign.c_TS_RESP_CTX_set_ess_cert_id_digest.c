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
struct TYPE_3__ {int /*<<< orphan*/  const* ess_cert_id_digest; } ;
typedef  TYPE_1__ TS_RESP_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */

int TS_RESP_CTX_set_ess_cert_id_digest(TS_RESP_CTX *ctx, const EVP_MD *md)
{
    ctx->ess_cert_id_digest = md;
    return 1;
}