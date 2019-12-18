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
typedef  scalar_t__ u32 ;
struct xdr_stream {int dummy; } ;
struct file_lock {void* fl_end; void* fl_start; int /*<<< orphan*/  fl_type; int /*<<< orphan*/  fl_flags; scalar_t__ fl_pid; } ;
struct nlm_lock {int /*<<< orphan*/  oh; void* svid; struct file_lock fl; } ;
struct nlm_res {struct nlm_lock lock; } ;
typedef  scalar_t__ s32 ;
typedef  scalar_t__ pid_t ;
typedef  void* loff_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  FL_POSIX ; 
 int /*<<< orphan*/  F_RDLCK ; 
 int /*<<< orphan*/  F_WRLCK ; 
 void* OFFSET_MAX ; 
 void* be32_to_cpup (int /*<<< orphan*/ *) ; 
 int decode_netobj (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  locks_init_lock (struct file_lock*) ; 
 int /*<<< orphan*/  memset (struct nlm_lock*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/ * xdr_inline_decode (struct xdr_stream*,int) ; 

__attribute__((used)) static int decode_nlm_holder(struct xdr_stream *xdr, struct nlm_res *result)
{
	struct nlm_lock *lock = &result->lock;
	struct file_lock *fl = &lock->fl;
	u32 exclusive, l_offset, l_len;
	int error;
	__be32 *p;
	s32 end;

	memset(lock, 0, sizeof(*lock));
	locks_init_lock(fl);

	p = xdr_inline_decode(xdr, 4 + 4);
	if (unlikely(p == NULL))
		goto out_overflow;
	exclusive = be32_to_cpup(p++);
	lock->svid = be32_to_cpup(p);
	fl->fl_pid = (pid_t)lock->svid;

	error = decode_netobj(xdr, &lock->oh);
	if (unlikely(error))
		goto out;

	p = xdr_inline_decode(xdr, 4 + 4);
	if (unlikely(p == NULL))
		goto out_overflow;

	fl->fl_flags = FL_POSIX;
	fl->fl_type  = exclusive != 0 ? F_WRLCK : F_RDLCK;
	l_offset = be32_to_cpup(p++);
	l_len = be32_to_cpup(p);
	end = l_offset + l_len - 1;

	fl->fl_start = (loff_t)l_offset;
	if (l_len == 0 || end < 0)
		fl->fl_end = OFFSET_MAX;
	else
		fl->fl_end = (loff_t)end;
	error = 0;
out:
	return error;
out_overflow:
	return -EIO;
}