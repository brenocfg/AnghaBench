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
struct visor_vbus_deviceinfo {int /*<<< orphan*/  infostrs; int /*<<< orphan*/  drvname; int /*<<< orphan*/ * devtype; } ;
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  isprint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static void vbuschannel_print_devinfo(struct visor_vbus_deviceinfo *devinfo,
				      struct seq_file *seq, int devix)
{
	/* uninitialized vbus device entry */
	if (!isprint(devinfo->devtype[0]))
		return;
	if (devix >= 0)
		seq_printf(seq, "[%d]", devix);
	else
		/* vbus device entry is for bus or chipset */
		seq_puts(seq, "   ");
	/*
	 * Note: because the s-Par back-end is free to scribble in this area,
	 * we never assume '\0'-termination.
	 */
	seq_printf(seq, "%-*.*s ", (int)sizeof(devinfo->devtype),
		   (int)sizeof(devinfo->devtype), devinfo->devtype);
	seq_printf(seq, "%-*.*s ", (int)sizeof(devinfo->drvname),
		   (int)sizeof(devinfo->drvname), devinfo->drvname);
	seq_printf(seq, "%.*s\n", (int)sizeof(devinfo->infostrs),
		   devinfo->infostrs);
}