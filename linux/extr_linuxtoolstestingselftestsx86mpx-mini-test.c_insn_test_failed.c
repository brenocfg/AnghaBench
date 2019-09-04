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
struct mpx_bt_entry {struct mpx_bt_entry** contents; } ;
struct mpx_bounds_dir {struct mpx_bounds_dir** contents; } ;
struct mpx_bd_entry {struct mpx_bd_entry** contents; } ;

/* Variables and functions */
 int /*<<< orphan*/  bd_entry_valid (struct mpx_bt_entry*) ; 
 scalar_t__ bounds_dir_ptr ; 
 int /*<<< orphan*/  eprintf (char*,int,int) ; 
 struct mpx_bt_entry* mpx_vaddr_to_bd_entry (void*,struct mpx_bt_entry*) ; 
 struct mpx_bt_entry* mpx_vaddr_to_bt_entry (void*,struct mpx_bt_entry*) ; 
 int /*<<< orphan*/  print_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  test_failed () ; 
 int /*<<< orphan*/  xsave_test_buf ; 

void insn_test_failed(int test_nr, int test_round, void *buf,
		void *buf_shadow, void *ptr)
{
	print_context(xsave_test_buf);
	eprintf("ERROR: test %d round %d failed\n", test_nr, test_round);
	while (test_nr == 5) {
		struct mpx_bt_entry *bte;
		struct mpx_bounds_dir *bd = (void *)bounds_dir_ptr;
		struct mpx_bd_entry *bde = mpx_vaddr_to_bd_entry(buf, bd);

		printf("  bd: %p\n", bd);
		printf("&bde: %p\n", bde);
		printf("*bde: %lx\n", *(unsigned long *)bde);
		if (!bd_entry_valid(bde))
			break;

		bte = mpx_vaddr_to_bt_entry(buf, bd);
		printf(" te: %p\n", bte);
		printf("bte[0]: %lx\n", bte->contents[0]);
		printf("bte[1]: %lx\n", bte->contents[1]);
		printf("bte[2]: %lx\n", bte->contents[2]);
		printf("bte[3]: %lx\n", bte->contents[3]);
		break;
	}
	test_failed();
}