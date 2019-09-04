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
struct ipr_resource_entry {int /*<<< orphan*/  ata_class; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_DEV_ATA ; 
 int /*<<< orphan*/  ATA_DEV_ATAPI ; 
 int /*<<< orphan*/  ATA_DEV_UNKNOWN ; 
#define  IPR_PROTO_SAS_STP 131 
#define  IPR_PROTO_SAS_STP_ATAPI 130 
#define  IPR_PROTO_SATA 129 
#define  IPR_PROTO_SATA_ATAPI 128 

__attribute__((used)) static void ipr_update_ata_class(struct ipr_resource_entry *res, unsigned int proto)
{
	switch (proto) {
	case IPR_PROTO_SATA:
	case IPR_PROTO_SAS_STP:
		res->ata_class = ATA_DEV_ATA;
		break;
	case IPR_PROTO_SATA_ATAPI:
	case IPR_PROTO_SAS_STP_ATAPI:
		res->ata_class = ATA_DEV_ATAPI;
		break;
	default:
		res->ata_class = ATA_DEV_UNKNOWN;
		break;
	};
}