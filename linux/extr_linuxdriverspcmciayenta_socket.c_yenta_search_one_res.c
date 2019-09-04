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
typedef  unsigned long u32 ;
struct resource {int flags; unsigned long end; unsigned long start; } ;

/* Variables and functions */
 unsigned long BRIDGE_IO_MAX ; 
 unsigned long BRIDGE_MEM_MAX ; 
 int IORESOURCE_IO ; 
 unsigned long PCIBIOS_MIN_CARDBUS_IO ; 
 unsigned long PCIBIOS_MIN_MEM ; 
 scalar_t__ allocate_resource (struct resource*,struct resource*,unsigned long,unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int yenta_search_one_res(struct resource *root, struct resource *res,
				u32 min)
{
	u32 align, size, start, end;

	if (res->flags & IORESOURCE_IO) {
		align = 1024;
		size = BRIDGE_IO_MAX;
		start = PCIBIOS_MIN_CARDBUS_IO;
		end = ~0U;
	} else {
		unsigned long avail = root->end - root->start;
		int i;
		size = BRIDGE_MEM_MAX;
		if (size > avail/8) {
			size = (avail+1)/8;
			/* round size down to next power of 2 */
			i = 0;
			while ((size /= 2) != 0)
				i++;
			size = 1 << i;
		}
		if (size < min)
			size = min;
		align = size;
		start = PCIBIOS_MIN_MEM;
		end = ~0U;
	}

	do {
		if (allocate_resource(root, res, size, start, end, align,
				      NULL, NULL) == 0) {
			return 1;
		}
		size = size/2;
		align = size;
	} while (size >= min);

	return 0;
}