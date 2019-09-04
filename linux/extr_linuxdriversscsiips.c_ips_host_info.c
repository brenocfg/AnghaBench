#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct seq_file {int dummy; } ;
struct TYPE_11__ {unsigned long count; } ;
struct TYPE_10__ {unsigned long count; } ;
struct TYPE_9__ {unsigned long count; } ;
struct TYPE_15__ {int ad_type; unsigned long max_cmds; unsigned long num_ioctl; TYPE_3__ copp_waitlist; TYPE_2__ scb_activelist; TYPE_1__ scb_waitlist; TYPE_6__* enq; TYPE_5__* nvram; TYPE_4__* pcidev; scalar_t__ mem_ptr; int /*<<< orphan*/  mem_len; scalar_t__ mem_addr; int /*<<< orphan*/  io_len; scalar_t__ io_addr; } ;
typedef  TYPE_7__ ips_ha_t ;
struct TYPE_14__ {unsigned long ucMaxPhysicalDevices; int /*<<< orphan*/ * BootBlkVersion; int /*<<< orphan*/ * CodeBlkVersion; } ;
struct TYPE_13__ {scalar_t__* bios_low; int /*<<< orphan*/ * bios_high; int /*<<< orphan*/  signature; int /*<<< orphan*/  adapter_type; } ;
struct TYPE_12__ {unsigned long irq; } ;

/* Variables and functions */
 unsigned long IPS_BUILD_IDENT ; 
 scalar_t__ IPS_NVRAM_P5_SIG ; 
 int /*<<< orphan*/  IPS_VERSION_HIGH ; 
 int /*<<< orphan*/  IPS_VERSION_LOW ; 
 int /*<<< orphan*/  METHOD_TRACE (char*,int) ; 
 unsigned long* ips_adapter_name ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,unsigned long,...) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int
ips_host_info(ips_ha_t *ha, struct seq_file *m)
{
	METHOD_TRACE("ips_host_info", 1);

	seq_puts(m, "\nIBM ServeRAID General Information:\n\n");

	if ((le32_to_cpu(ha->nvram->signature) == IPS_NVRAM_P5_SIG) &&
	    (le16_to_cpu(ha->nvram->adapter_type) != 0))
		seq_printf(m, "\tController Type                   : %s\n",
			  ips_adapter_name[ha->ad_type - 1]);
	else
		seq_puts(m, "\tController Type                   : Unknown\n");

	if (ha->io_addr)
		seq_printf(m,
			  "\tIO region                         : 0x%x (%d bytes)\n",
			  ha->io_addr, ha->io_len);

	if (ha->mem_addr) {
		seq_printf(m,
			  "\tMemory region                     : 0x%x (%d bytes)\n",
			  ha->mem_addr, ha->mem_len);
		seq_printf(m,
			  "\tShared memory address             : 0x%lx\n",
			  (unsigned long)ha->mem_ptr);
	}

	seq_printf(m, "\tIRQ number                        : %d\n", ha->pcidev->irq);

    /* For the Next 3 lines Check for Binary 0 at the end and don't include it if it's there. */
    /* That keeps everything happy for "text" operations on the proc file.                    */

	if (le32_to_cpu(ha->nvram->signature) == IPS_NVRAM_P5_SIG) {
	if (ha->nvram->bios_low[3] == 0) {
		seq_printf(m,
			  "\tBIOS Version                      : %c%c%c%c%c%c%c\n",
			  ha->nvram->bios_high[0], ha->nvram->bios_high[1],
			  ha->nvram->bios_high[2], ha->nvram->bios_high[3],
			  ha->nvram->bios_low[0], ha->nvram->bios_low[1],
			  ha->nvram->bios_low[2]);

        } else {
		seq_printf(m,
			  "\tBIOS Version                      : %c%c%c%c%c%c%c%c\n",
			  ha->nvram->bios_high[0], ha->nvram->bios_high[1],
			  ha->nvram->bios_high[2], ha->nvram->bios_high[3],
			  ha->nvram->bios_low[0], ha->nvram->bios_low[1],
			  ha->nvram->bios_low[2], ha->nvram->bios_low[3]);
        }

    }

    if (ha->enq->CodeBlkVersion[7] == 0) {
        seq_printf(m,
		  "\tFirmware Version                  : %c%c%c%c%c%c%c\n",
		  ha->enq->CodeBlkVersion[0], ha->enq->CodeBlkVersion[1],
		  ha->enq->CodeBlkVersion[2], ha->enq->CodeBlkVersion[3],
		  ha->enq->CodeBlkVersion[4], ha->enq->CodeBlkVersion[5],
		  ha->enq->CodeBlkVersion[6]);
    } else {
	seq_printf(m,
		  "\tFirmware Version                  : %c%c%c%c%c%c%c%c\n",
		  ha->enq->CodeBlkVersion[0], ha->enq->CodeBlkVersion[1],
		  ha->enq->CodeBlkVersion[2], ha->enq->CodeBlkVersion[3],
		  ha->enq->CodeBlkVersion[4], ha->enq->CodeBlkVersion[5],
		  ha->enq->CodeBlkVersion[6], ha->enq->CodeBlkVersion[7]);
    }

    if (ha->enq->BootBlkVersion[7] == 0) {
        seq_printf(m,
		  "\tBoot Block Version                : %c%c%c%c%c%c%c\n",
		  ha->enq->BootBlkVersion[0], ha->enq->BootBlkVersion[1],
		  ha->enq->BootBlkVersion[2], ha->enq->BootBlkVersion[3],
		  ha->enq->BootBlkVersion[4], ha->enq->BootBlkVersion[5],
		  ha->enq->BootBlkVersion[6]);
    } else {
        seq_printf(m,
		  "\tBoot Block Version                : %c%c%c%c%c%c%c%c\n",
		  ha->enq->BootBlkVersion[0], ha->enq->BootBlkVersion[1],
		  ha->enq->BootBlkVersion[2], ha->enq->BootBlkVersion[3],
		  ha->enq->BootBlkVersion[4], ha->enq->BootBlkVersion[5],
		  ha->enq->BootBlkVersion[6], ha->enq->BootBlkVersion[7]);
    }

	seq_printf(m, "\tDriver Version                    : %s%s\n",
		  IPS_VERSION_HIGH, IPS_VERSION_LOW);

	seq_printf(m, "\tDriver Build                      : %d\n",
		  IPS_BUILD_IDENT);

	seq_printf(m, "\tMax Physical Devices              : %d\n",
		  ha->enq->ucMaxPhysicalDevices);
	seq_printf(m, "\tMax Active Commands               : %d\n",
		  ha->max_cmds);
	seq_printf(m, "\tCurrent Queued Commands           : %d\n",
		  ha->scb_waitlist.count);
	seq_printf(m, "\tCurrent Active Commands           : %d\n",
		  ha->scb_activelist.count - ha->num_ioctl);
	seq_printf(m, "\tCurrent Queued PT Commands        : %d\n",
		  ha->copp_waitlist.count);
	seq_printf(m, "\tCurrent Active PT Commands        : %d\n",
		  ha->num_ioctl);

	seq_putc(m, '\n');

	return 0;
}