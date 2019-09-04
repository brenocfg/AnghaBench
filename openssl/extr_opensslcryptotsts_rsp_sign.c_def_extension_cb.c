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
typedef  int /*<<< orphan*/  X509_EXTENSION ;

/* Variables and functions */
 int /*<<< orphan*/  TS_INFO_UNACCEPTED_EXTENSION ; 
 int /*<<< orphan*/  TS_RESP_CTX_add_failure_info (struct TS_resp_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TS_RESP_CTX_set_status_info (struct TS_resp_ctx*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TS_STATUS_REJECTION ; 

__attribute__((used)) static int def_extension_cb(struct TS_resp_ctx *ctx, X509_EXTENSION *ext,
                            void *data)
{
    TS_RESP_CTX_set_status_info(ctx, TS_STATUS_REJECTION,
                                "Unsupported extension.");
    TS_RESP_CTX_add_failure_info(ctx, TS_INFO_UNACCEPTED_EXTENSION);
    return 0;
}