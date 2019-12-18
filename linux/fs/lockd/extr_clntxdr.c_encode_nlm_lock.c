#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct xdr_stream {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct nlm_lock {int /*<<< orphan*/  svid; TYPE_1__ oh; int /*<<< orphan*/  fh; int /*<<< orphan*/  caller; } ;
typedef  void* __be32 ;

/* Variables and functions */
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode_caller_name (struct xdr_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode_fh (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  encode_netobj (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_compute_offsets (struct nlm_lock const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void** xdr_reserve_space (struct xdr_stream*,int) ; 

__attribute__((used)) static void encode_nlm_lock(struct xdr_stream *xdr,
			    const struct nlm_lock *lock)
{
	u32 l_offset, l_len;
	__be32 *p;

	encode_caller_name(xdr, lock->caller);
	encode_fh(xdr, &lock->fh);
	encode_netobj(xdr, lock->oh.data, lock->oh.len);

	p = xdr_reserve_space(xdr, 4 + 4 + 4);
	*p++ = cpu_to_be32(lock->svid);

	nlm_compute_offsets(lock, &l_offset, &l_len);
	*p++ = cpu_to_be32(l_offset);
	*p   = cpu_to_be32(l_len);
}