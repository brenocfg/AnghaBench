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
struct of_bus {scalar_t__ (* map ) (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int,int) ;int (* translate ) (int /*<<< orphan*/ *,scalar_t__,int) ;} ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ OF_BAD_ADDR ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  of_dump_addr (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  of_empty_ranges_quirk (struct device_node*) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char const*,unsigned int*) ; 
 scalar_t__ of_read_number (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int,int) ; 
 int stub2 (int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static int of_translate_one(struct device_node *parent, struct of_bus *bus,
			    struct of_bus *pbus, __be32 *addr,
			    int na, int ns, int pna, const char *rprop)
{
	const __be32 *ranges;
	unsigned int rlen;
	int rone;
	u64 offset = OF_BAD_ADDR;

	/*
	 * Normally, an absence of a "ranges" property means we are
	 * crossing a non-translatable boundary, and thus the addresses
	 * below the current cannot be converted to CPU physical ones.
	 * Unfortunately, while this is very clear in the spec, it's not
	 * what Apple understood, and they do have things like /uni-n or
	 * /ht nodes with no "ranges" property and a lot of perfectly
	 * useable mapped devices below them. Thus we treat the absence of
	 * "ranges" as equivalent to an empty "ranges" property which means
	 * a 1:1 translation at that level. It's up to the caller not to try
	 * to translate addresses that aren't supposed to be translated in
	 * the first place. --BenH.
	 *
	 * As far as we know, this damage only exists on Apple machines, so
	 * This code is only enabled on powerpc. --gcl
	 */
	ranges = of_get_property(parent, rprop, &rlen);
	if (ranges == NULL && !of_empty_ranges_quirk(parent)) {
		pr_debug("no ranges; cannot translate\n");
		return 1;
	}
	if (ranges == NULL || rlen == 0) {
		offset = of_read_number(addr, na);
		memset(addr, 0, pna * 4);
		pr_debug("empty ranges; 1:1 translation\n");
		goto finish;
	}

	pr_debug("walking ranges...\n");

	/* Now walk through the ranges */
	rlen /= 4;
	rone = na + pna + ns;
	for (; rlen >= rone; rlen -= rone, ranges += rone) {
		offset = bus->map(addr, ranges, na, ns, pna);
		if (offset != OF_BAD_ADDR)
			break;
	}
	if (offset == OF_BAD_ADDR) {
		pr_debug("not found !\n");
		return 1;
	}
	memcpy(addr, ranges + na, 4 * pna);

 finish:
	of_dump_addr("parent translation for:", addr, pna);
	pr_debug("with offset: %llx\n", (unsigned long long)offset);

	/* Translate it into parent bus space */
	return pbus->translate(addr, offset, pna);
}