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
struct TYPE_2__ {void* code; void* len; } ;
struct fwserial_mgmt_pkt {TYPE_1__ hdr; } ;

/* Variables and functions */
 int FWSC_RSP_NACK ; 
 int FWSC_VIRT_CABLE_PLUG_RSP ; 
 void* cpu_to_be16 (int) ; 
 int mgmt_pkt_expected_len (void*) ; 

__attribute__((used)) static inline void fill_plug_rsp_nack(struct fwserial_mgmt_pkt *pkt)
{
	pkt->hdr.code = cpu_to_be16(FWSC_VIRT_CABLE_PLUG_RSP | FWSC_RSP_NACK);
	pkt->hdr.len = cpu_to_be16(mgmt_pkt_expected_len(pkt->hdr.code));
}