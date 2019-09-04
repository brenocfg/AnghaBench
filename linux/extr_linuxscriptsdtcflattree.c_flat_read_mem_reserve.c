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
typedef  scalar_t__ uint64_t ;
struct reserve_info {int dummy; } ;
struct inbuf {int dummy; } ;
struct fdt_reserve_entry {int /*<<< orphan*/  size; int /*<<< orphan*/  address; } ;
typedef  int /*<<< orphan*/  re ;

/* Variables and functions */
 struct reserve_info* add_reserve_entry (struct reserve_info*,struct reserve_info*) ; 
 struct reserve_info* build_reserve_entry (scalar_t__,scalar_t__) ; 
 scalar_t__ fdt64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flat_read_chunk (struct inbuf*,struct fdt_reserve_entry*,int) ; 

__attribute__((used)) static struct reserve_info *flat_read_mem_reserve(struct inbuf *inb)
{
	struct reserve_info *reservelist = NULL;
	struct reserve_info *new;
	struct fdt_reserve_entry re;

	/*
	 * Each entry is a pair of u64 (addr, size) values for 4 cell_t's.
	 * List terminates at an entry with size equal to zero.
	 *
	 * First pass, count entries.
	 */
	while (1) {
		uint64_t address, size;

		flat_read_chunk(inb, &re, sizeof(re));
		address  = fdt64_to_cpu(re.address);
		size = fdt64_to_cpu(re.size);
		if (size == 0)
			break;

		new = build_reserve_entry(address, size);
		reservelist = add_reserve_entry(reservelist, new);
	}

	return reservelist;
}