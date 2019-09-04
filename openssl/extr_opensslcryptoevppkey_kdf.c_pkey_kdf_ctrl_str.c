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
struct TYPE_3__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_KDF_CTX ;

/* Variables and functions */
 int EVP_KDF_ctrl_str (int /*<<< orphan*/ *,char const*,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int pkey_kdf_ctrl_str(EVP_PKEY_CTX *ctx, const char *type,
                             const char *value)
{
    EVP_KDF_CTX *kctx = ctx->data;

    if (strcmp(type, "md") == 0)
        return EVP_KDF_ctrl_str(kctx, "digest", value);
    return EVP_KDF_ctrl_str(kctx, type, value);
}