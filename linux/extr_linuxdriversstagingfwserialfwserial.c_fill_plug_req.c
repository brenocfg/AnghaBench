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
struct fwtty_port {int dummy; } ;
struct TYPE_2__ {void* code; void* len; } ;
struct fwserial_mgmt_pkt {int /*<<< orphan*/  plug_req; TYPE_1__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  FWSC_VIRT_CABLE_PLUG ; 
 void* cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_plug_params (int /*<<< orphan*/ *,struct fwtty_port*) ; 
 int /*<<< orphan*/  mgmt_pkt_expected_len (void*) ; 

__attribute__((used)) static inline void fill_plug_req(struct fwserial_mgmt_pkt *pkt,
				 struct fwtty_port *port)
{
	pkt->hdr.code = cpu_to_be16(FWSC_VIRT_CABLE_PLUG);
	pkt->hdr.len = cpu_to_be16(mgmt_pkt_expected_len(pkt->hdr.code));
	fill_plug_params(&pkt->plug_req, port);
}