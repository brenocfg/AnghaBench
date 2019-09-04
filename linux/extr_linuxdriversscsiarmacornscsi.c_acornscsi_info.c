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
struct Scsi_Host {TYPE_1__* hostt; int /*<<< orphan*/  irq; int /*<<< orphan*/  io_port; } ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  VER_MAJOR ; 
 int /*<<< orphan*/  VER_MINOR ; 
 int /*<<< orphan*/  VER_PATCH ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

const
char *acornscsi_info(struct Scsi_Host *host)
{
    static char string[100], *p;

    p = string;
    
    p += sprintf(string, "%s at port %08lX irq %d v%d.%d.%d"
#ifdef CONFIG_SCSI_ACORNSCSI_SYNC
    " SYNC"
#endif
#ifdef CONFIG_SCSI_ACORNSCSI_TAGGED_QUEUE
    " TAG"
#endif
#if (DEBUG & DEBUG_NO_WRITE)
    " NOWRITE (" __stringify(NO_WRITE) ")"
#endif
		, host->hostt->name, host->io_port, host->irq,
		VER_MAJOR, VER_MINOR, VER_PATCH);
    return string;
}