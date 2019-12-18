#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct TS_resp_ctx {int dummy; } ;
typedef  int /*<<< orphan*/  ASN1_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/ * ASN1_INTEGER_new () ; 
 int /*<<< orphan*/  ASN1_INTEGER_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  TS_F_DEF_SERIAL_CB ; 
 int /*<<< orphan*/  TS_RESP_CTX_set_status_info (struct TS_resp_ctx*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TS_STATUS_REJECTION ; 
 int /*<<< orphan*/  TSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ASN1_INTEGER *def_serial_cb(struct TS_resp_ctx *ctx, void *data)
{
    ASN1_INTEGER *serial = ASN1_INTEGER_new();

    if (serial == NULL)
        goto err;
    if (!ASN1_INTEGER_set(serial, 1))
        goto err;
    return serial;

 err:
    TSerr(TS_F_DEF_SERIAL_CB, ERR_R_MALLOC_FAILURE);
    TS_RESP_CTX_set_status_info(ctx, TS_STATUS_REJECTION,
                                "Error during serial number generation.");
    return NULL;
}