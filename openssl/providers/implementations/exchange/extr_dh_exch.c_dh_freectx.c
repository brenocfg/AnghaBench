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
struct TYPE_3__ {int /*<<< orphan*/  dhpeer; int /*<<< orphan*/  dh; } ;
typedef  TYPE_1__ PROV_DH_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  DH_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 

__attribute__((used)) static void dh_freectx(void *vpdhctx)
{
    PROV_DH_CTX *pdhctx = (PROV_DH_CTX *)vpdhctx;

    DH_free(pdhctx->dh);
    DH_free(pdhctx->dhpeer);

    OPENSSL_free(pdhctx);
}