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
struct TYPE_2__ {int /*<<< orphan*/  AttrInt; } ;
struct lpfc_fdmi_attr_entry {TYPE_1__ un; } ;
struct lpfc_fdmi_attr_def {void* AttrType; void* AttrLen; int /*<<< orphan*/  AttrValue; } ;

/* Variables and functions */
 int FC_COS_CLASS2 ; 
 int FC_COS_CLASS3 ; 
 int FOURBYTES ; 
 int RPRT_SUPPORTED_CLASS ; 
 void* cpu_to_be16 (int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 

__attribute__((used)) static int
lpfc_fdmi_port_attr_class(struct lpfc_vport *vport,
			  struct lpfc_fdmi_attr_def *ad)
{
	struct lpfc_fdmi_attr_entry *ae;
	uint32_t size;

	ae = (struct lpfc_fdmi_attr_entry *)&ad->AttrValue;
	ae->un.AttrInt = cpu_to_be32(FC_COS_CLASS2 | FC_COS_CLASS3);
	size = FOURBYTES + sizeof(uint32_t);
	ad->AttrLen = cpu_to_be16(size);
	ad->AttrType = cpu_to_be16(RPRT_SUPPORTED_CLASS);
	return size;
}