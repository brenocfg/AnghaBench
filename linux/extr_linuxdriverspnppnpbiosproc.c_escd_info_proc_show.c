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
struct seq_file {int dummy; } ;
struct escd_info_struc {int /*<<< orphan*/  nv_storage_base; int /*<<< orphan*/  escd_size; int /*<<< orphan*/  min_escd_write_size; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ pnp_bios_escd_info (struct escd_info_struc*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int escd_info_proc_show(struct seq_file *m, void *v)
{
	struct escd_info_struc escd;

	if (pnp_bios_escd_info(&escd))
		return -EIO;
	seq_printf(m, "min_ESCD_write_size %d\n"
			"ESCD_size %d\n"
			"NVRAM_base 0x%x\n",
			escd.min_escd_write_size,
			escd.escd_size, escd.nv_storage_base);
	return 0;
}