#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_5__ {TYPE_1__* dctx; } ;
struct TYPE_4__ {size_t mdmax; int /*<<< orphan*/  const** mdevp; } ;
typedef  TYPE_2__ SSL_DANE ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */

__attribute__((used)) static const EVP_MD *tlsa_md_get(SSL_DANE *dane, uint8_t mtype)
{
    if (mtype > dane->dctx->mdmax)
        return NULL;
    return dane->dctx->mdevp[mtype];
}