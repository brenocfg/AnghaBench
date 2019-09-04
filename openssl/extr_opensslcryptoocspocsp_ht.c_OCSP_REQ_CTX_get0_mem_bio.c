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
struct TYPE_3__ {int /*<<< orphan*/ * mem; } ;
typedef  TYPE_1__ OCSP_REQ_CTX ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */

BIO *OCSP_REQ_CTX_get0_mem_bio(OCSP_REQ_CTX *rctx)
{
    return rctx->mem;
}