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
struct TYPE_2__ {int /*<<< orphan*/  er_Type; } ;
struct zorro_dev {TYPE_1__ rom; int /*<<< orphan*/  id; } ;
struct seq_file {int dummy; } ;
typedef  unsigned int loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,unsigned int,int /*<<< orphan*/ ,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 struct zorro_dev* zorro_autocon ; 
 scalar_t__ zorro_resource_len (struct zorro_dev*) ; 
 scalar_t__ zorro_resource_start (struct zorro_dev*) ; 

__attribute__((used)) static int zorro_seq_show(struct seq_file *m, void *v)
{
	unsigned int slot = *(loff_t *)v;
	struct zorro_dev *z = &zorro_autocon[slot];

	seq_printf(m, "%02x\t%08x\t%08lx\t%08lx\t%02x\n", slot, z->id,
		   (unsigned long)zorro_resource_start(z),
		   (unsigned long)zorro_resource_len(z),
		   z->rom.er_Type);
	return 0;
}