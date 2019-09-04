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
typedef  int uint32_t ;
struct lpfc_vport {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  AttrString; } ;
struct lpfc_fdmi_attr_entry {TYPE_1__ un; } ;
struct lpfc_fdmi_attr_def {void* AttrType; void* AttrLen; int /*<<< orphan*/  AttrValue; } ;

/* Variables and functions */
 int FOURBYTES ; 
 int RPRT_SMART_SERVICE ; 
 void* cpu_to_be16 (int) ; 
 int /*<<< orphan*/  memset (struct lpfc_fdmi_attr_entry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 
 int strnlen (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
lpfc_fdmi_smart_attr_service(struct lpfc_vport *vport,
			     struct lpfc_fdmi_attr_def *ad)
{
	struct lpfc_fdmi_attr_entry *ae;
	uint32_t len, size;

	ae = (struct lpfc_fdmi_attr_entry *)&ad->AttrValue;
	memset(ae, 0, 256);

	strncpy(ae->un.AttrString, "Smart SAN Initiator",
		sizeof(ae->un.AttrString));
	len = strnlen(ae->un.AttrString,
			  sizeof(ae->un.AttrString));
	len += (len & 3) ? (4 - (len & 3)) : 4;
	size = FOURBYTES + len;
	ad->AttrLen = cpu_to_be16(size);
	ad->AttrType = cpu_to_be16(RPRT_SMART_SERVICE);
	return size;
}