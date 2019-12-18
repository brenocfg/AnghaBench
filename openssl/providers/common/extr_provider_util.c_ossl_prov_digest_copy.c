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
struct TYPE_4__ {int /*<<< orphan*/ * alloc_md; int /*<<< orphan*/  md; int /*<<< orphan*/  engine; } ;
typedef  TYPE_1__ PROV_DIGEST ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_MD_up_ref (int /*<<< orphan*/ *) ; 

int ossl_prov_digest_copy(PROV_DIGEST *dst, const PROV_DIGEST *src)
{
    if (src->alloc_md != NULL && !EVP_MD_up_ref(src->alloc_md))
        return 0;
    dst->engine = src->engine;
    dst->md = src->md;
    dst->alloc_md = src->alloc_md;
    return 1;
}