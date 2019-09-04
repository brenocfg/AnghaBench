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
struct item_head {int dummy; } ;

/* Variables and functions */
 int ih_item_len (struct item_head*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static void direct_print_item(struct item_head *ih, char *item)
{
	int j = 0;

/*    return; */
	printk("\"");
	while (j < ih_item_len(ih))
		printk("%c", item[j++]);
	printk("\"\n");
}