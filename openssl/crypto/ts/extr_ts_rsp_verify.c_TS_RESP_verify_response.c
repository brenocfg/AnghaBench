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
struct TYPE_4__ {int /*<<< orphan*/ * tst_info; int /*<<< orphan*/ * token; } ;
typedef  int /*<<< orphan*/  TS_VERIFY_CTX ;
typedef  int /*<<< orphan*/  TS_TST_INFO ;
typedef  TYPE_1__ TS_RESP ;
typedef  int /*<<< orphan*/  PKCS7 ;

/* Variables and functions */
 int /*<<< orphan*/  int_ts_RESP_verify_token (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_check_status_info (TYPE_1__*) ; 

int TS_RESP_verify_response(TS_VERIFY_CTX *ctx, TS_RESP *response)
{
    PKCS7 *token = response->token;
    TS_TST_INFO *tst_info = response->tst_info;
    int ret = 0;

    if (!ts_check_status_info(response))
        goto err;
    if (!int_ts_RESP_verify_token(ctx, token, tst_info))
        goto err;
    ret = 1;

 err:
    return ret;
}