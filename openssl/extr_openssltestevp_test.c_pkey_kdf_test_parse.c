#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* data; } ;
struct TYPE_5__ {int /*<<< orphan*/  ctx; int /*<<< orphan*/  output_len; int /*<<< orphan*/  output; } ;
typedef  TYPE_1__ PKEY_KDF_DATA ;
typedef  TYPE_2__ EVP_TEST ;

/* Variables and functions */
 int parse_bin (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pkey_test_ctrl (TYPE_2__*,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static int pkey_kdf_test_parse(EVP_TEST *t,
                               const char *keyword, const char *value)
{
    PKEY_KDF_DATA *kdata = t->data;

    if (strcmp(keyword, "Output") == 0)
        return parse_bin(value, &kdata->output, &kdata->output_len);
    if (strncmp(keyword, "Ctrl", 4) == 0)
        return pkey_test_ctrl(t, kdata->ctx, value);
    return 0;
}