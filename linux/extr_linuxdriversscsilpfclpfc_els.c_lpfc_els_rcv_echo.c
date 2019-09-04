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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct lpfc_vport {int dummy; } ;
struct lpfc_nodelist {int dummy; } ;
struct lpfc_iocbq {scalar_t__ context2; } ;
struct lpfc_dmabuf {scalar_t__ virt; } ;

/* Variables and functions */
 int /*<<< orphan*/  lpfc_els_rsp_echo_acc (struct lpfc_vport*,int /*<<< orphan*/ *,struct lpfc_iocbq*,struct lpfc_nodelist*) ; 

__attribute__((used)) static int
lpfc_els_rcv_echo(struct lpfc_vport *vport, struct lpfc_iocbq *cmdiocb,
		  struct lpfc_nodelist *ndlp)
{
	uint8_t *pcmd;

	pcmd = (uint8_t *) (((struct lpfc_dmabuf *) cmdiocb->context2)->virt);

	/* skip over first word of echo command to find echo data */
	pcmd += sizeof(uint32_t);

	lpfc_els_rsp_echo_acc(vport, pcmd, cmdiocb, ndlp);
	return 0;
}