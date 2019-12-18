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
struct TYPE_3__ {int /*<<< orphan*/ * engine; int /*<<< orphan*/ * md; int /*<<< orphan*/ * alloc_md; } ;
typedef  TYPE_1__ PROV_DIGEST ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_MD_free (int /*<<< orphan*/ *) ; 

void ossl_prov_digest_reset(PROV_DIGEST *pd)
{
    EVP_MD_free(pd->alloc_md);
    pd->alloc_md = NULL;
    pd->md = NULL;
    pd->engine = NULL;
}