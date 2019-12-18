#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_4__* ssl; TYPE_2__* ctx; } ;
struct TYPE_12__ {TYPE_3__* method; } ;
struct TYPE_11__ {TYPE_5__* ctx; } ;
struct TYPE_10__ {int version; } ;
struct TYPE_9__ {TYPE_1__* method; } ;
struct TYPE_8__ {int version; } ;
typedef  TYPE_6__ SSL_CONF_CTX ;

/* Variables and functions */
 int protocol_from_string (char const*) ; 
 int ssl_set_version_bound (int,int,int*) ; 

__attribute__((used)) static int min_max_proto(SSL_CONF_CTX *cctx, const char *value, int *bound)
{
    int method_version;
    int new_version;

    if (cctx->ctx != NULL)
        method_version = cctx->ctx->method->version;
    else if (cctx->ssl != NULL)
        method_version = cctx->ssl->ctx->method->version;
    else
        return 0;
    if ((new_version = protocol_from_string(value)) < 0)
        return 0;
    return ssl_set_version_bound(method_version, new_version, bound);
}