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
typedef  int /*<<< orphan*/  TS_VERIFY_CTX ;
typedef  int /*<<< orphan*/  TS_TST_INFO ;
typedef  int /*<<< orphan*/  PKCS7 ;

/* Variables and functions */
 int /*<<< orphan*/ * PKCS7_to_TS_TST_INFO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TS_TST_INFO_free (int /*<<< orphan*/ *) ; 
 int int_ts_RESP_verify_token (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int TS_RESP_verify_token(TS_VERIFY_CTX *ctx, PKCS7 *token)
{
    TS_TST_INFO *tst_info = PKCS7_to_TS_TST_INFO(token);
    int ret = 0;
    if (tst_info) {
        ret = int_ts_RESP_verify_token(ctx, token, tst_info);
        TS_TST_INFO_free(tst_info);
    }
    return ret;
}