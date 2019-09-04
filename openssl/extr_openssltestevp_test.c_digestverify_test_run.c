#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  output_len; int /*<<< orphan*/  output; int /*<<< orphan*/  ctx; int /*<<< orphan*/  input; } ;
struct TYPE_4__ {char* err; TYPE_2__* data; } ;
typedef  TYPE_1__ EVP_TEST ;
typedef  TYPE_2__ DIGESTSIGN_DATA ;

/* Variables and functions */
 scalar_t__ EVP_DigestVerifyFinal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  digestverify_update_fn ; 
 int /*<<< orphan*/  evp_test_buffer_do (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int digestverify_test_run(EVP_TEST *t)
{
    DIGESTSIGN_DATA *mdata = t->data;

    if (!evp_test_buffer_do(mdata->input, digestverify_update_fn, mdata->ctx)) {
        t->err = "DIGESTUPDATE_ERROR";
        return 1;
    }

    if (EVP_DigestVerifyFinal(mdata->ctx, mdata->output,
                              mdata->output_len) <= 0)
        t->err = "VERIFY_ERROR";
    return 1;
}