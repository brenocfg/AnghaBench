#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct user_desc {int dummy; } ;
struct TYPE_5__ {int entry_number; unsigned long base_addr; int limit; int seg_32bit; int read_exec_only; int limit_in_pages; int seg_not_present; scalar_t__ useable; scalar_t__ contents; } ;

/* Variables and functions */
 int MAP_32BIT ; 
 int MAP_ANONYMOUS ; 
 TYPE_1__* MAP_FAILED ; 
 int MAP_PRIVATE ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/ * counter_page ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int gdt_entry_num ; 
 scalar_t__ invoke_set_thread_area () ; 
 TYPE_1__* low_user_desc ; 
 TYPE_1__* low_user_desc_clear ; 
 TYPE_1__* mmap (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void setup_low_user_desc(void)
{
	low_user_desc = mmap(NULL, 2 * sizeof(struct user_desc),
			     PROT_READ | PROT_WRITE,
			     MAP_ANONYMOUS | MAP_PRIVATE | MAP_32BIT, -1, 0);
	if (low_user_desc == MAP_FAILED)
		err(1, "mmap");

	low_user_desc->entry_number	= -1;
	low_user_desc->base_addr	= (unsigned long)&counter_page[1];
	low_user_desc->limit		= 0xfffff;
	low_user_desc->seg_32bit	= 1;
	low_user_desc->contents		= 0; /* Data, grow-up*/
	low_user_desc->read_exec_only	= 0;
	low_user_desc->limit_in_pages	= 1;
	low_user_desc->seg_not_present	= 0;
	low_user_desc->useable		= 0;

	if (invoke_set_thread_area() == 0) {
		gdt_entry_num = low_user_desc->entry_number;
		printf("[NOTE]\tset_thread_area is available; will use GDT index %d\n", gdt_entry_num);
	} else {
		printf("[NOTE]\tset_thread_area is unavailable\n");
	}

	low_user_desc_clear = low_user_desc + 1;
	low_user_desc_clear->entry_number = gdt_entry_num;
	low_user_desc_clear->read_exec_only = 1;
	low_user_desc_clear->seg_not_present = 1;
}