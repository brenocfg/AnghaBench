#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ disable_mdc; } ;
typedef  int /*<<< orphan*/  PushFilter ;
typedef  TYPE_1__ PGP_Context ;

/* Variables and functions */
 int PGP_PKT_SYMENCRYPTED_DATA ; 
 int PGP_PKT_SYMENCRYPTED_DATA_MDC ; 
 int /*<<< orphan*/  pkt_stream_filter ; 
 int pushf_create (int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int write_tag_only (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
init_encdata_packet(PushFilter **pf_res, PGP_Context *ctx, PushFilter *dst)
{
	int			res;
	int			tag;

	if (ctx->disable_mdc)
		tag = PGP_PKT_SYMENCRYPTED_DATA;
	else
		tag = PGP_PKT_SYMENCRYPTED_DATA_MDC;

	res = write_tag_only(dst, tag);
	if (res < 0)
		return res;

	return pushf_create(pf_res, &pkt_stream_filter, ctx, dst);
}