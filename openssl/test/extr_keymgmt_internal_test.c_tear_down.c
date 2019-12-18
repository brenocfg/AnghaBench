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
struct TYPE_4__ {int /*<<< orphan*/  ctx2; int /*<<< orphan*/  ctx1; int /*<<< orphan*/  prov2; int /*<<< orphan*/  prov1; } ;
typedef  TYPE_1__ FIXTURE ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_CTX_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/  OSSL_PROVIDER_unload (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tear_down(FIXTURE *fixture)
{
    if (fixture != NULL) {
        OSSL_PROVIDER_unload(fixture->prov1);
        OSSL_PROVIDER_unload(fixture->prov2);
        OPENSSL_CTX_free(fixture->ctx1);
        OPENSSL_CTX_free(fixture->ctx2);
        OPENSSL_free(fixture);
    }
}