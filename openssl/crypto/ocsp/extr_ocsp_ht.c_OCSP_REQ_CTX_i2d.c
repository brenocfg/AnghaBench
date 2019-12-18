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
typedef  int /*<<< orphan*/  ASN1_VALUE ;
typedef  int /*<<< orphan*/  ASN1_ITEM ;

/* Variables and functions */
 int ASN1_item_i2d (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 scalar_t__ ASN1_item_i2d_bio (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ BIO_printf (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  OHS_ASN1_WRITE_INIT ; 

int OCSP_REQ_CTX_i2d(OCSP_REQ_CTX *rctx, const ASN1_ITEM *it, ASN1_VALUE *val)
{
    static const char req_hdr[] =
        "Content-Type: application/ocsp-request\r\n"
        "Content-Length: %d\r\n\r\n";
    int reqlen = ASN1_item_i2d(val, NULL, it);
    if (BIO_printf(rctx->mem, req_hdr, reqlen) <= 0)
        return 0;
    if (ASN1_item_i2d_bio(it, rctx->mem, val) <= 0)
        return 0;
    rctx->state = OHS_ASN1_WRITE_INIT;
    return 1;
}