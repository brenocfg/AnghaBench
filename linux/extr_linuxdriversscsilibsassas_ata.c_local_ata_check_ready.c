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
struct sas_internal {TYPE_1__* dft; } ;
struct domain_device {int dummy; } ;
struct ata_port {struct domain_device* private_data; } ;
struct ata_link {struct ata_port* ap; } ;
struct TYPE_2__ {int (* lldd_ata_check_ready ) (struct domain_device*) ;} ;

/* Variables and functions */
 struct sas_internal* dev_to_sas_internal (struct domain_device*) ; 
 int stub1 (struct domain_device*) ; 

__attribute__((used)) static int local_ata_check_ready(struct ata_link *link)
{
	struct ata_port *ap = link->ap;
	struct domain_device *dev = ap->private_data;
	struct sas_internal *i = dev_to_sas_internal(dev);

	if (i->dft->lldd_ata_check_ready)
		return i->dft->lldd_ata_check_ready(dev);
	else {
		/* lldd's that don't implement 'ready' checking get the
		 * old default behavior of not coordinating reset
		 * recovery with libata
		 */
		return 1;
	}
}