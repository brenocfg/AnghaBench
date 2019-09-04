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
struct expansion_card {int /*<<< orphan*/  dev; } ;
struct ecard_id {int dummy; } ;
struct Scsi_Host {int /*<<< orphan*/  irq; } ;
struct NCR5380_hostdata {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  io; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECARD_RES_MEMC ; 
 int ENOMEM ; 
 int FLAG_DMA_FIXUP ; 
 int FLAG_LATE_DMA_SETUP ; 
 int /*<<< orphan*/  NCR5380_exit (struct Scsi_Host*) ; 
 int NCR5380_init (struct Scsi_Host*,int) ; 
 int /*<<< orphan*/  NCR5380_maybe_reset_bus (struct Scsi_Host*) ; 
 int /*<<< orphan*/  NO_IRQ ; 
 int /*<<< orphan*/  ecard_release_resources (struct expansion_card*) ; 
 int ecard_request_resources (struct expansion_card*) ; 
 int /*<<< orphan*/  ecard_resource_len (struct expansion_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecard_resource_start (struct expansion_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oakscsi_template ; 
 TYPE_1__* priv (struct Scsi_Host*) ; 
 int scsi_add_host (struct Scsi_Host*,int /*<<< orphan*/ *) ; 
 struct Scsi_Host* scsi_host_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_scan_host (struct Scsi_Host*) ; 

__attribute__((used)) static int oakscsi_probe(struct expansion_card *ec, const struct ecard_id *id)
{
	struct Scsi_Host *host;
	int ret = -ENOMEM;

	ret = ecard_request_resources(ec);
	if (ret)
		goto out;

	host = scsi_host_alloc(&oakscsi_template, sizeof(struct NCR5380_hostdata));
	if (!host) {
		ret = -ENOMEM;
		goto release;
	}

	priv(host)->io = ioremap(ecard_resource_start(ec, ECARD_RES_MEMC),
	                         ecard_resource_len(ec, ECARD_RES_MEMC));
	if (!priv(host)->io) {
		ret = -ENOMEM;
		goto unreg;
	}

	host->irq = NO_IRQ;

	ret = NCR5380_init(host, FLAG_DMA_FIXUP | FLAG_LATE_DMA_SETUP);
	if (ret)
		goto out_unmap;

	NCR5380_maybe_reset_bus(host);

	ret = scsi_add_host(host, &ec->dev);
	if (ret)
		goto out_exit;

	scsi_scan_host(host);
	goto out;

 out_exit:
	NCR5380_exit(host);
 out_unmap:
	iounmap(priv(host)->io);
 unreg:
	scsi_host_put(host);
 release:
	ecard_release_resources(ec);
 out:
	return ret;
}