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
struct TYPE_3__ {int /*<<< orphan*/ * bn; scalar_t__ too_many; scalar_t__ depth; scalar_t__ flags; scalar_t__ tos; } ;
typedef  TYPE_1__ BN_CTX ;

/* Variables and functions */
 int BN_CTX_NUM ; 
 int /*<<< orphan*/  BN_init (int /*<<< orphan*/ *) ; 

void BN_CTX_init(BN_CTX *ctx)
	{
	int i;
	ctx->tos = 0;
	ctx->flags = 0;
	ctx->depth = 0;
	ctx->too_many = 0;
	for (i = 0; i < BN_CTX_NUM; i++)
		BN_init(&(ctx->bn[i]));
	}