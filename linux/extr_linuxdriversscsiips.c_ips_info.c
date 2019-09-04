#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct Scsi_Host {int dummy; } ;
struct TYPE_3__ {int ad_type; } ;
typedef  TYPE_1__ ips_ha_t ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  IPS_BUILD_IDENT ; 
 TYPE_1__* IPS_HA (struct Scsi_Host*) ; 
 char* IPS_VERSION_HIGH ; 
 int IPS_VERSION_LOW ; 
 int MAX_ADAPTER_NAME ; 
 int /*<<< orphan*/  METHOD_TRACE (char*,int) ; 
 char** ips_adapter_name ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 

__attribute__((used)) static const char *
ips_info(struct Scsi_Host *SH)
{
	static char buffer[256];
	char *bp;
	ips_ha_t *ha;

	METHOD_TRACE("ips_info", 1);

	ha = IPS_HA(SH);

	if (!ha)
		return (NULL);

	bp = &buffer[0];
	memset(bp, 0, sizeof (buffer));

	sprintf(bp, "%s%s%s Build %d", "IBM PCI ServeRAID ",
		IPS_VERSION_HIGH, IPS_VERSION_LOW, IPS_BUILD_IDENT);

	if (ha->ad_type > 0 && ha->ad_type <= MAX_ADAPTER_NAME) {
		strcat(bp, " <");
		strcat(bp, ips_adapter_name[ha->ad_type - 1]);
		strcat(bp, ">");
	}

	return (bp);
}