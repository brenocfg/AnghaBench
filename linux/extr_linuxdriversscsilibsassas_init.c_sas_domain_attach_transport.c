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
struct scsi_transport_template {int create_work_queue; int /*<<< orphan*/  eh_strategy_handler; } ;
struct sas_internal {struct sas_domain_function_template* dft; } ;
struct sas_domain_function_template {int dummy; } ;

/* Variables and functions */
 struct scsi_transport_template* sas_attach_transport (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sas_scsi_recover_host ; 
 int /*<<< orphan*/  sft ; 
 struct sas_internal* to_sas_internal (struct scsi_transport_template*) ; 

struct scsi_transport_template *
sas_domain_attach_transport(struct sas_domain_function_template *dft)
{
	struct scsi_transport_template *stt = sas_attach_transport(&sft);
	struct sas_internal *i;

	if (!stt)
		return stt;

	i = to_sas_internal(stt);
	i->dft = dft;
	stt->create_work_queue = 1;
	stt->eh_strategy_handler = sas_scsi_recover_host;

	return stt;
}