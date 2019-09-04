#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_3__ {int revision; int gs_type; int gs_subtype; } ;
struct ct_sns_req {void* max_rsp_size; void* command; TYPE_1__ header; } ;
struct TYPE_4__ {struct ct_sns_req req; } ;
struct ct_sns_pkt {TYPE_2__ p; } ;

/* Variables and functions */
 void* cpu_to_be16 (int) ; 
 int /*<<< orphan*/  memset (struct ct_sns_pkt*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline struct ct_sns_req *
qla24xx_prep_ct_fm_req(struct ct_sns_pkt *p, uint16_t cmd,
    uint16_t rsp_size)
{
	memset(p, 0, sizeof(struct ct_sns_pkt));

	p->p.req.header.revision = 0x01;
	p->p.req.header.gs_type = 0xFA;
	p->p.req.header.gs_subtype = 0x01;
	p->p.req.command = cpu_to_be16(cmd);
	p->p.req.max_rsp_size = cpu_to_be16((rsp_size - 16) / 4);

	return &p->p.req;
}