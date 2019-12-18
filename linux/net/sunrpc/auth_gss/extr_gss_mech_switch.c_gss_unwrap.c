#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct xdr_buf {int dummy; } ;
struct gss_ctx {TYPE_2__* mech_type; } ;
struct TYPE_4__ {TYPE_1__* gm_ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* gss_unwrap ) (struct gss_ctx*,int,struct xdr_buf*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct gss_ctx*,int,struct xdr_buf*) ; 

u32
gss_unwrap(struct gss_ctx	*ctx_id,
	   int			offset,
	   struct xdr_buf	*buf)
{
	return ctx_id->mech_type->gm_ops
		->gss_unwrap(ctx_id, offset, buf);
}