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
struct bpf_object {int /*<<< orphan*/  kern_version; int /*<<< orphan*/  path; } ;
typedef  int /*<<< orphan*/  kver ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int LIBBPF_ERRNO__FORMAT ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bpf_object__init_kversion(struct bpf_object *obj, void *data, size_t size)
{
	__u32 kver;

	if (size != sizeof(kver)) {
		pr_warning("invalid kver section in %s\n", obj->path);
		return -LIBBPF_ERRNO__FORMAT;
	}
	memcpy(&kver, data, sizeof(kver));
	obj->kern_version = kver;
	pr_debug("kernel version of %s is %x\n", obj->path, obj->kern_version);
	return 0;
}