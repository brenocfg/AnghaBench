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
struct TYPE_4__ {int /*<<< orphan*/  cmp_ctx; int /*<<< orphan*/  hdr; } ;
typedef  TYPE_1__ CMP_HDR_TEST_FIXTURE ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/  OSSL_CMP_CTX_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSSL_CMP_PKIHEADER_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tear_down(CMP_HDR_TEST_FIXTURE *fixture)
{
    OSSL_CMP_PKIHEADER_free(fixture->hdr);
    OSSL_CMP_CTX_free(fixture->cmp_ctx);
    OPENSSL_free(fixture);
}