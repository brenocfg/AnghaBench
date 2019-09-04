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
struct xenpf_pcpuinfo {int flags; int /*<<< orphan*/  xen_cpuid; } ;
struct pcpu {int flags; int /*<<< orphan*/  list; int /*<<< orphan*/  cpu_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct pcpu* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int XEN_PCPU_FLAGS_INVALID ; 
 struct pcpu* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int register_pcpu (struct pcpu*) ; 
 int /*<<< orphan*/  xen_pcpus ; 

__attribute__((used)) static struct pcpu *create_and_register_pcpu(struct xenpf_pcpuinfo *info)
{
	struct pcpu *pcpu;
	int err;

	if (info->flags & XEN_PCPU_FLAGS_INVALID)
		return ERR_PTR(-ENODEV);

	pcpu = kzalloc(sizeof(struct pcpu), GFP_KERNEL);
	if (!pcpu)
		return ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&pcpu->list);
	pcpu->cpu_id = info->xen_cpuid;
	pcpu->flags = info->flags;

	/* Need hold on xen_pcpu_lock before pcpu list manipulations */
	list_add_tail(&pcpu->list, &xen_pcpus);

	err = register_pcpu(pcpu);
	if (err) {
		pr_warn("Failed to register pcpu%u\n", info->xen_cpuid);
		return ERR_PTR(-ENOENT);
	}

	return pcpu;
}