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
struct TYPE_5__ {scalar_t__ linked; } ;
typedef  TYPE_1__ context_t ;
struct TYPE_6__ {int /*<<< orphan*/  ctx; } ;
typedef  TYPE_2__ cert_t ;
typedef  int /*<<< orphan*/  WINECRYPT_CERTSTORE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CertDeleteCertificateFromStore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static BOOL Collection_deleteCert(WINECRYPT_CERTSTORE *store, context_t *context)
{
    cert_t *cert = (cert_t*)context;
    cert_t *linked;

    TRACE("(%p, %p)\n", store, cert);

    linked = (cert_t*)context->linked;
    return CertDeleteCertificateFromStore(&linked->ctx);
}