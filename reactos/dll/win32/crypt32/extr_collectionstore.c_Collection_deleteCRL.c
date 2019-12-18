#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ crl_t ;
struct TYPE_6__ {scalar_t__ linked; } ;
typedef  TYPE_2__ context_t ;
typedef  int /*<<< orphan*/  WINECRYPT_CERTSTORE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CertDeleteCRLFromStore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static BOOL Collection_deleteCRL(WINECRYPT_CERTSTORE *store, context_t *context)
{
    crl_t *crl = (crl_t*)context, *linked;

    TRACE("(%p, %p)\n", store, crl);

    linked = (crl_t*)context->linked;
    return CertDeleteCRLFromStore(&linked->ctx);
}