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
struct TYPE_3__ {int disable_mdc; } ;
typedef  TYPE_1__ PGP_Context ;

/* Variables and functions */

int
pgp_disable_mdc(PGP_Context *ctx, int disable)
{
	ctx->disable_mdc = disable ? 1 : 0;
	return 0;
}