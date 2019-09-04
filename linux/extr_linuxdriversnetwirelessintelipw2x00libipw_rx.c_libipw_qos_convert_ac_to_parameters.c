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
typedef  int u8 ;
typedef  int u32 ;
struct libipw_qos_parameters {int* aifs; int* flag; void** tx_op_limit; void** cw_max; void** cw_min; } ;
struct libipw_qos_parameter_info {struct libipw_qos_ac_parameter* ac_params_record; } ;
struct libipw_qos_ac_parameter {int aci_aifsn; int ecw_min_max; int /*<<< orphan*/  tx_op_limit; } ;

/* Variables and functions */
 int QOS_QUEUE_NUM ; 
 void* cpu_to_le16 (int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int libipw_qos_convert_ac_to_parameters(struct
						  libipw_qos_parameter_info
						  *param_elm, struct
						  libipw_qos_parameters
						  *qos_param)
{
	int rc = 0;
	int i;
	struct libipw_qos_ac_parameter *ac_params;
	u32 txop;
	u8 cw_min;
	u8 cw_max;

	for (i = 0; i < QOS_QUEUE_NUM; i++) {
		ac_params = &(param_elm->ac_params_record[i]);

		qos_param->aifs[i] = (ac_params->aci_aifsn) & 0x0F;
		qos_param->aifs[i] -= (qos_param->aifs[i] < 2) ? 0 : 2;

		cw_min = ac_params->ecw_min_max & 0x0F;
		qos_param->cw_min[i] = cpu_to_le16((1 << cw_min) - 1);

		cw_max = (ac_params->ecw_min_max & 0xF0) >> 4;
		qos_param->cw_max[i] = cpu_to_le16((1 << cw_max) - 1);

		qos_param->flag[i] =
		    (ac_params->aci_aifsn & 0x10) ? 0x01 : 0x00;

		txop = le16_to_cpu(ac_params->tx_op_limit) * 32;
		qos_param->tx_op_limit[i] = cpu_to_le16(txop);
	}
	return rc;
}