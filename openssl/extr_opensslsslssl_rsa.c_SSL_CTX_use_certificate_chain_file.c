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
 int use_certificate_chain_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 

int SSL_CTX_use_certificate_chain_file(SSL_CTX *ctx, const char *file)
{
    return use_certificate_chain_file(ctx, NULL, file);
}