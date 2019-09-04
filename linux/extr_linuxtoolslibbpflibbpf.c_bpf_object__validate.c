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
struct bpf_object {scalar_t__ kern_version; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int LIBBPF_ERRNO__KVERSION ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bpf_object__validate(struct bpf_object *obj, bool needs_kver)
{
	if (needs_kver && obj->kern_version == 0) {
		pr_warning("%s doesn't provide kernel version\n",
			   obj->path);
		return -LIBBPF_ERRNO__KVERSION;
	}
	return 0;
}