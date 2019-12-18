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
 int /*<<< orphan*/  SSL_CTX_load_verify_dir (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  SSL_CTX_load_verify_file (int /*<<< orphan*/ *,char const*) ; 

int SSL_CTX_load_verify_locations(SSL_CTX *ctx, const char *CAfile,
                                  const char *CApath)
{
    if (CAfile == NULL && CApath == NULL)
        return 0;
    if (CAfile != NULL && !SSL_CTX_load_verify_file(ctx, CAfile))
        return 0;
    if (CApath != NULL && !SSL_CTX_load_verify_dir(ctx, CApath))
        return 0;
    return 1;
}