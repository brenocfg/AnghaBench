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
struct whc {int n_devices; struct di_buf_entry* di_buf; } ;
struct seq_file {struct whc* private; } ;
struct di_buf_entry {int addr_sec_info; scalar_t__ availability_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  UWB_NUM_MAS ; 
 int WHC_DI_DEV_ADDR_MASK ; 
 int WHC_DI_DISABLE ; 
 int WHC_DI_KEY_IDX_MASK ; 
 int WHC_DI_SECURE ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char,...) ; 

__attribute__((used)) static int di_show(struct seq_file *s, void *p)
{
	struct whc *whc = s->private;
	int d;

	for (d = 0; d < whc->n_devices; d++) {
		struct di_buf_entry *di = &whc->di_buf[d];

		seq_printf(s, "DI[%d]\n", d);
		seq_printf(s, "  availability: %*pb\n",
			   UWB_NUM_MAS, (unsigned long *)di->availability_info);
		seq_printf(s, "  %c%c key idx: %d dev addr: %d\n",
			   (di->addr_sec_info & WHC_DI_SECURE) ? 'S' : ' ',
			   (di->addr_sec_info & WHC_DI_DISABLE) ? 'D' : ' ',
			   (di->addr_sec_info & WHC_DI_KEY_IDX_MASK) >> 8,
			   (di->addr_sec_info & WHC_DI_DEV_ADDR_MASK));
	}
	return 0;
}