#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  verify_mode; TYPE_1__* cert; int /*<<< orphan*/  max_proto_version; int /*<<< orphan*/  min_proto_version; int /*<<< orphan*/  options; } ;
struct TYPE_7__ {int /*<<< orphan*/ * pvfy_flags; int /*<<< orphan*/ * pcert_flags; int /*<<< orphan*/ * max_version; int /*<<< orphan*/ * min_version; int /*<<< orphan*/ * poptions; int /*<<< orphan*/ * ctx; TYPE_3__* ssl; } ;
struct TYPE_6__ {int /*<<< orphan*/  cert_flags; } ;
typedef  TYPE_2__ SSL_CONF_CTX ;
typedef  TYPE_3__ SSL ;

/* Variables and functions */

void SSL_CONF_CTX_set_ssl(SSL_CONF_CTX *cctx, SSL *ssl)
{
    cctx->ssl = ssl;
    cctx->ctx = NULL;
    if (ssl) {
        cctx->poptions = &ssl->options;
        cctx->min_version = &ssl->min_proto_version;
        cctx->max_version = &ssl->max_proto_version;
        cctx->pcert_flags = &ssl->cert->cert_flags;
        cctx->pvfy_flags = &ssl->verify_mode;
    } else {
        cctx->poptions = NULL;
        cctx->min_version = NULL;
        cctx->max_version = NULL;
        cctx->pcert_flags = NULL;
        cctx->pvfy_flags = NULL;
    }
}