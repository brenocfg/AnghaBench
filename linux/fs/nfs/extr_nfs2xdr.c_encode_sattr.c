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
typedef  int /*<<< orphan*/  u32 ;
struct xdr_stream {int dummy; } ;
struct user_namespace {int dummy; } ;
struct timespec {int dummy; } ;
struct iattr {int ia_valid; int /*<<< orphan*/  ia_mtime; int /*<<< orphan*/  ia_atime; scalar_t__ ia_size; int /*<<< orphan*/  ia_gid; int /*<<< orphan*/  ia_uid; int /*<<< orphan*/  ia_mode; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ATTR_ATIME ; 
 int ATTR_ATIME_SET ; 
 int ATTR_GID ; 
 int ATTR_MODE ; 
 int ATTR_MTIME ; 
 int ATTR_MTIME_SET ; 
 int ATTR_SIZE ; 
 int ATTR_UID ; 
 int /*<<< orphan*/  NFS2_SATTR_NOT_SET ; 
 int NFS_sattr_sz ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  from_kgid_munged (struct user_namespace*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  from_kuid_munged (struct user_namespace*,int /*<<< orphan*/ ) ; 
 struct timespec timespec64_to_timespec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_encode_current_server_time (int /*<<< orphan*/ *,struct timespec*) ; 
 int /*<<< orphan*/ * xdr_encode_time (int /*<<< orphan*/ *,struct timespec*) ; 
 int /*<<< orphan*/ * xdr_reserve_space (struct xdr_stream*,int) ; 
 int /*<<< orphan*/ * xdr_time_not_set (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void encode_sattr(struct xdr_stream *xdr, const struct iattr *attr,
		struct user_namespace *userns)
{
	struct timespec ts;
	__be32 *p;

	p = xdr_reserve_space(xdr, NFS_sattr_sz << 2);

	if (attr->ia_valid & ATTR_MODE)
		*p++ = cpu_to_be32(attr->ia_mode);
	else
		*p++ = cpu_to_be32(NFS2_SATTR_NOT_SET);
	if (attr->ia_valid & ATTR_UID)
		*p++ = cpu_to_be32(from_kuid_munged(userns, attr->ia_uid));
	else
		*p++ = cpu_to_be32(NFS2_SATTR_NOT_SET);
	if (attr->ia_valid & ATTR_GID)
		*p++ = cpu_to_be32(from_kgid_munged(userns, attr->ia_gid));
	else
		*p++ = cpu_to_be32(NFS2_SATTR_NOT_SET);
	if (attr->ia_valid & ATTR_SIZE)
		*p++ = cpu_to_be32((u32)attr->ia_size);
	else
		*p++ = cpu_to_be32(NFS2_SATTR_NOT_SET);

	if (attr->ia_valid & ATTR_ATIME_SET) {
		ts = timespec64_to_timespec(attr->ia_atime);
		p = xdr_encode_time(p, &ts);
	} else if (attr->ia_valid & ATTR_ATIME) {
		ts = timespec64_to_timespec(attr->ia_atime);
		p = xdr_encode_current_server_time(p, &ts);
	} else
		p = xdr_time_not_set(p);
	if (attr->ia_valid & ATTR_MTIME_SET) {
		ts = timespec64_to_timespec(attr->ia_atime);
		xdr_encode_time(p, &ts);
	} else if (attr->ia_valid & ATTR_MTIME) {
		ts = timespec64_to_timespec(attr->ia_mtime);
		xdr_encode_current_server_time(p, &ts);
	} else
		xdr_time_not_set(p);
}