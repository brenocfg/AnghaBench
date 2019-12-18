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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct xdr_stream {int dummy; } ;
struct user_namespace {int dummy; } ;
struct timespec {int dummy; } ;
struct iattr {int ia_valid; int ia_mode; int /*<<< orphan*/  ia_mtime; int /*<<< orphan*/  ia_atime; scalar_t__ ia_size; int /*<<< orphan*/  ia_gid; int /*<<< orphan*/  ia_uid; } ;
typedef  void* __be32 ;

/* Variables and functions */
 int ATTR_ATIME ; 
 int ATTR_ATIME_SET ; 
 int ATTR_GID ; 
 int ATTR_MODE ; 
 int ATTR_MTIME ; 
 int ATTR_MTIME_SET ; 
 int ATTR_SIZE ; 
 int ATTR_UID ; 
 int S_IALLUGO ; 
 void* cpu_to_be32 (int) ; 
 int from_kgid_munged (struct user_namespace*,int /*<<< orphan*/ ) ; 
 int from_kuid_munged (struct user_namespace*,int /*<<< orphan*/ ) ; 
 struct timespec timespec64_to_timespec (int /*<<< orphan*/ ) ; 
 void** xdr_encode_hyper (void**,int /*<<< orphan*/ ) ; 
 void** xdr_encode_nfstime3 (void**,struct timespec*) ; 
 void* xdr_one ; 
 void** xdr_reserve_space (struct xdr_stream*,int) ; 
 void* xdr_two ; 
 void* xdr_zero ; 

__attribute__((used)) static void encode_sattr3(struct xdr_stream *xdr, const struct iattr *attr,
		struct user_namespace *userns)
{
	struct timespec ts;
	u32 nbytes;
	__be32 *p;

	/*
	 * In order to make only a single xdr_reserve_space() call,
	 * pre-compute the total number of bytes to be reserved.
	 * Six boolean values, one for each set_foo field, are always
	 * present in the encoded result, so start there.
	 */
	nbytes = 6 * 4;
	if (attr->ia_valid & ATTR_MODE)
		nbytes += 4;
	if (attr->ia_valid & ATTR_UID)
		nbytes += 4;
	if (attr->ia_valid & ATTR_GID)
		nbytes += 4;
	if (attr->ia_valid & ATTR_SIZE)
		nbytes += 8;
	if (attr->ia_valid & ATTR_ATIME_SET)
		nbytes += 8;
	if (attr->ia_valid & ATTR_MTIME_SET)
		nbytes += 8;
	p = xdr_reserve_space(xdr, nbytes);

	if (attr->ia_valid & ATTR_MODE) {
		*p++ = xdr_one;
		*p++ = cpu_to_be32(attr->ia_mode & S_IALLUGO);
	} else
		*p++ = xdr_zero;

	if (attr->ia_valid & ATTR_UID) {
		*p++ = xdr_one;
		*p++ = cpu_to_be32(from_kuid_munged(userns, attr->ia_uid));
	} else
		*p++ = xdr_zero;

	if (attr->ia_valid & ATTR_GID) {
		*p++ = xdr_one;
		*p++ = cpu_to_be32(from_kgid_munged(userns, attr->ia_gid));
	} else
		*p++ = xdr_zero;

	if (attr->ia_valid & ATTR_SIZE) {
		*p++ = xdr_one;
		p = xdr_encode_hyper(p, (u64)attr->ia_size);
	} else
		*p++ = xdr_zero;

	if (attr->ia_valid & ATTR_ATIME_SET) {
		struct timespec ts;
		*p++ = xdr_two;
		ts = timespec64_to_timespec(attr->ia_atime);
		p = xdr_encode_nfstime3(p, &ts);
	} else if (attr->ia_valid & ATTR_ATIME) {
		*p++ = xdr_one;
	} else
		*p++ = xdr_zero;

	if (attr->ia_valid & ATTR_MTIME_SET) {
		*p++ = xdr_two;
		ts = timespec64_to_timespec(attr->ia_mtime);
		xdr_encode_nfstime3(p, &ts);
	} else if (attr->ia_valid & ATTR_MTIME) {
		*p = xdr_one;
	} else
		*p = xdr_zero;
}