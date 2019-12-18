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
struct TYPE_3__ {int /*<<< orphan*/  state; int /*<<< orphan*/  mem; } ;
typedef  TYPE_1__ OCSP_REQ_CTX ;

/* Variables and functions */
 scalar_t__ BIO_printf (int /*<<< orphan*/ ,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  OHS_HTTP_HEADER ; 

int OCSP_REQ_CTX_http(OCSP_REQ_CTX *rctx, const char *op, const char *path)
{
    static const char http_hdr[] = "%s %s HTTP/1.0\r\n";

    if (path == NULL)
        path = "/";

    if (BIO_printf(rctx->mem, http_hdr, op, path) <= 0)
        return 0;
    rctx->state = OHS_HTTP_HEADER;
    return 1;
}