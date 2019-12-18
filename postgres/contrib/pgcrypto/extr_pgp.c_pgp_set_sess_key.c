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
struct TYPE_3__ {int use_sess_key; } ;
typedef  TYPE_1__ PGP_Context ;

/* Variables and functions */

int
pgp_set_sess_key(PGP_Context *ctx, int use)
{
	ctx->use_sess_key = use ? 1 : 0;
	return 0;
}