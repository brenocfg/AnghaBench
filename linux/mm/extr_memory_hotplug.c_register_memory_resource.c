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
typedef  scalar_t__ u64 ;
struct resource {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  E2BIG ; 
 int /*<<< orphan*/  EEXIST ; 
 struct resource* ERR_PTR (int /*<<< orphan*/ ) ; 
 unsigned long IORESOURCE_BUSY ; 
 unsigned long IORESOURCE_SYSTEM_RAM ; 
 struct resource* __request_region (int /*<<< orphan*/ *,scalar_t__,scalar_t__,char*,unsigned long) ; 
 int /*<<< orphan*/  iomem_resource ; 
 scalar_t__ max_mem_size ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static struct resource *register_memory_resource(u64 start, u64 size)
{
	struct resource *res;
	unsigned long flags =  IORESOURCE_SYSTEM_RAM | IORESOURCE_BUSY;
	char *resource_name = "System RAM";

	if (start + size > max_mem_size)
		return ERR_PTR(-E2BIG);

	/*
	 * Request ownership of the new memory range.  This might be
	 * a child of an existing resource that was present but
	 * not marked as busy.
	 */
	res = __request_region(&iomem_resource, start, size,
			       resource_name, flags);

	if (!res) {
		pr_debug("Unable to reserve System RAM region: %016llx->%016llx\n",
				start, start + size);
		return ERR_PTR(-EEXIST);
	}
	return res;
}