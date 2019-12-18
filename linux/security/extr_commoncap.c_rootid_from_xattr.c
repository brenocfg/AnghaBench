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
typedef  int /*<<< orphan*/  uid_t ;
struct vfs_ns_cap_data {int /*<<< orphan*/  rootid; } ;
struct user_namespace {int dummy; } ;
typedef  int /*<<< orphan*/  kuid_t ;

/* Variables and functions */
 size_t XATTR_CAPS_SZ_3 ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_kuid (struct user_namespace*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static kuid_t rootid_from_xattr(const void *value, size_t size,
				struct user_namespace *task_ns)
{
	const struct vfs_ns_cap_data *nscap = value;
	uid_t rootid = 0;

	if (size == XATTR_CAPS_SZ_3)
		rootid = le32_to_cpu(nscap->rootid);

	return make_kuid(task_ns, rootid);
}