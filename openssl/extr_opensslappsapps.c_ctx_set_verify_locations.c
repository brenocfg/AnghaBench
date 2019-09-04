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
typedef  int /*<<< orphan*/  SSL_CTX ;

/* Variables and functions */
 int SSL_CTX_load_verify_locations (int /*<<< orphan*/ *,char const*,char const*) ; 
 scalar_t__ SSL_CTX_set_default_verify_dir (int /*<<< orphan*/ *) ; 
 scalar_t__ SSL_CTX_set_default_verify_file (int /*<<< orphan*/ *) ; 

int ctx_set_verify_locations(SSL_CTX *ctx, const char *CAfile,
                             const char *CApath, int noCAfile, int noCApath)
{
    if (CAfile == NULL && CApath == NULL) {
        if (!noCAfile && SSL_CTX_set_default_verify_file(ctx) <= 0)
            return 0;
        if (!noCApath && SSL_CTX_set_default_verify_dir(ctx) <= 0)
            return 0;

        return 1;
    }
    return SSL_CTX_load_verify_locations(ctx, CAfile, CApath);
}