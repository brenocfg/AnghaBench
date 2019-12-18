#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ pub_key; } ;
typedef  TYPE_1__ PGP_Context ;

/* Variables and functions */
 int /*<<< orphan*/  pgp_key_free (scalar_t__) ; 
 int /*<<< orphan*/  px_free (TYPE_1__*) ; 
 int /*<<< orphan*/  px_memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

int
pgp_free(PGP_Context *ctx)
{
	if (ctx->pub_key)
		pgp_key_free(ctx->pub_key);
	px_memset(ctx, 0, sizeof *ctx);
	px_free(ctx);
	return 0;
}