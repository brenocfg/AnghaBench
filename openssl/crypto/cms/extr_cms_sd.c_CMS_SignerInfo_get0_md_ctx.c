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
struct TYPE_3__ {int /*<<< orphan*/ * mctx; } ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  TYPE_1__ CMS_SignerInfo ;

/* Variables and functions */

EVP_MD_CTX *CMS_SignerInfo_get0_md_ctx(CMS_SignerInfo *si)
{
    return si->mctx;
}