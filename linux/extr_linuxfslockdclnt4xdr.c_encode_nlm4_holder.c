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
typedef  int /*<<< orphan*/  u64 ;
struct xdr_stream {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_4__ {scalar_t__ fl_type; } ;
struct nlm_lock {TYPE_1__ oh; int /*<<< orphan*/  svid; TYPE_2__ fl; } ;
struct nlm_res {struct nlm_lock lock; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ F_RDLCK ; 
 int /*<<< orphan*/  encode_bool (struct xdr_stream*,int) ; 
 int /*<<< orphan*/  encode_int32 (struct xdr_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode_netobj (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm4_compute_offsets (struct nlm_lock const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xdr_encode_hyper (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_reserve_space (struct xdr_stream*,int) ; 

__attribute__((used)) static void encode_nlm4_holder(struct xdr_stream *xdr,
			       const struct nlm_res *result)
{
	const struct nlm_lock *lock = &result->lock;
	u64 l_offset, l_len;
	__be32 *p;

	encode_bool(xdr, lock->fl.fl_type == F_RDLCK);
	encode_int32(xdr, lock->svid);
	encode_netobj(xdr, lock->oh.data, lock->oh.len);

	p = xdr_reserve_space(xdr, 4 + 4);
	nlm4_compute_offsets(lock, &l_offset, &l_len);
	p = xdr_encode_hyper(p, l_offset);
	xdr_encode_hyper(p, l_len);
}