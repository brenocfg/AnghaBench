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
 scalar_t__ BIO_puts (int /*<<< orphan*/ ,char const*) ; 
 int BIO_write (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  OHS_HTTP_HEADER ; 

int OCSP_REQ_CTX_add1_header(OCSP_REQ_CTX *rctx,
                             const char *name, const char *value)
{
    if (!name)
        return 0;
    if (BIO_puts(rctx->mem, name) <= 0)
        return 0;
    if (value) {
        if (BIO_write(rctx->mem, ": ", 2) != 2)
            return 0;
        if (BIO_puts(rctx->mem, value) <= 0)
            return 0;
    }
    if (BIO_write(rctx->mem, "\r\n", 2) != 2)
        return 0;
    rctx->state = OHS_HTTP_HEADER;
    return 1;
}