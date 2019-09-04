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
struct eisa_scsi_data {struct Scsi_Host** host; } ;
struct device {int dummy; } ;
struct Scsi_Host {int io_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASC_IOADR_GAP ; 
 int /*<<< orphan*/  advansys_release (struct Scsi_Host*) ; 
 struct eisa_scsi_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  kfree (struct eisa_scsi_data*) ; 
 int /*<<< orphan*/  release_region (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int advansys_eisa_remove(struct device *dev)
{
	int i;
	struct eisa_scsi_data *data = dev_get_drvdata(dev);

	for (i = 0; i < 2; i++) {
		int ioport;
		struct Scsi_Host *shost = data->host[i];
		if (!shost)
			continue;
		ioport = shost->io_port;
		advansys_release(shost);
		release_region(ioport, ASC_IOADR_GAP);
	}

	kfree(data);
	return 0;
}