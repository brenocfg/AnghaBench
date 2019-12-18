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
struct util_store_cap_data {scalar_t__ engine; scalar_t__ ok; int /*<<< orphan*/  cap_size; int /*<<< orphan*/  cap_buf; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  OSSL_STORE_LOADER ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ OSSL_STORE_LOADER_get0_engine (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  OSSL_STORE_LOADER_get0_scheme (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  append_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void util_store_cap(const OSSL_STORE_LOADER *loader, void *arg)
{
    struct util_store_cap_data *ctx = arg;

    if (OSSL_STORE_LOADER_get0_engine(loader) == ctx->engine) {
        char buf[256];
        BIO_snprintf(buf, sizeof(buf), "STORE(%s)",
                     OSSL_STORE_LOADER_get0_scheme(loader));
        if (!append_buf(ctx->cap_buf, ctx->cap_size, buf))
            ctx->ok = 0;
    }
}