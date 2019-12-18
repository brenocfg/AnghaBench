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
typedef  int u32 ;
struct vgic_its {TYPE_1__* dev; } ;
struct kvm {int dummy; } ;
typedef  size_t gpa_t ;
typedef  int (* entry_fn_t ) (struct vgic_its*,int,char*,void*) ;
struct TYPE_2__ {struct kvm* kvm; } ;

/* Variables and functions */
 int ESZ_MAX ; 
 int kvm_read_guest_lock (struct kvm*,size_t,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int scan_its_table(struct vgic_its *its, gpa_t base, int size, u32 esz,
			  int start_id, entry_fn_t fn, void *opaque)
{
	struct kvm *kvm = its->dev->kvm;
	unsigned long len = size;
	int id = start_id;
	gpa_t gpa = base;
	char entry[ESZ_MAX];
	int ret;

	memset(entry, 0, esz);

	while (len > 0) {
		int next_offset;
		size_t byte_offset;

		ret = kvm_read_guest_lock(kvm, gpa, entry, esz);
		if (ret)
			return ret;

		next_offset = fn(its, id, entry, opaque);
		if (next_offset <= 0)
			return next_offset;

		byte_offset = next_offset * esz;
		id += next_offset;
		gpa += byte_offset;
		len -= byte_offset;
	}
	return 1;
}