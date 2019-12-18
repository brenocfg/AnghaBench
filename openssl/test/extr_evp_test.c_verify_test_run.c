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
struct TYPE_5__ {char* err; TYPE_1__* data; } ;
struct TYPE_4__ {int /*<<< orphan*/  input_len; int /*<<< orphan*/  input; int /*<<< orphan*/  output_len; int /*<<< orphan*/  output; int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ PKEY_DATA ;
typedef  TYPE_2__ EVP_TEST ;

/* Variables and functions */
 scalar_t__ EVP_PKEY_verify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int verify_test_run(EVP_TEST *t)
{
    PKEY_DATA *kdata = t->data;

    if (EVP_PKEY_verify(kdata->ctx, kdata->output, kdata->output_len,
                        kdata->input, kdata->input_len) <= 0)
        t->err = "VERIFY_ERROR";
    return 1;
}