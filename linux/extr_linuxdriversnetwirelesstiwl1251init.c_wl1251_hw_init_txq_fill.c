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
struct acx_tx_queue_qos_config {int qid; int high_threshold; int low_threshold; } ;

/* Variables and functions */
 int EINVAL ; 
#define  QOS_AC_BE 131 
#define  QOS_AC_BK 130 
#define  QOS_AC_VI 129 
#define  QOS_AC_VO 128 
 int QOS_TX_HIGH_BE_DEF ; 
 int QOS_TX_HIGH_BK_DEF ; 
 int QOS_TX_HIGH_VI_DEF ; 
 int QOS_TX_HIGH_VO_DEF ; 
 int QOS_TX_LOW_BE_DEF ; 
 int QOS_TX_LOW_BK_DEF ; 
 int QOS_TX_LOW_VI_DEF ; 
 int QOS_TX_LOW_VO_DEF ; 
 int /*<<< orphan*/  wl1251_error (char*,int) ; 

__attribute__((used)) static int wl1251_hw_init_txq_fill(u8 qid,
				   struct acx_tx_queue_qos_config *config,
				   u32 num_blocks)
{
	config->qid = qid;

	switch (qid) {
	case QOS_AC_BE:
		config->high_threshold =
			(QOS_TX_HIGH_BE_DEF * num_blocks) / 100;
		config->low_threshold =
			(QOS_TX_LOW_BE_DEF * num_blocks) / 100;
		break;
	case QOS_AC_BK:
		config->high_threshold =
			(QOS_TX_HIGH_BK_DEF * num_blocks) / 100;
		config->low_threshold =
			(QOS_TX_LOW_BK_DEF * num_blocks) / 100;
		break;
	case QOS_AC_VI:
		config->high_threshold =
			(QOS_TX_HIGH_VI_DEF * num_blocks) / 100;
		config->low_threshold =
			(QOS_TX_LOW_VI_DEF * num_blocks) / 100;
		break;
	case QOS_AC_VO:
		config->high_threshold =
			(QOS_TX_HIGH_VO_DEF * num_blocks) / 100;
		config->low_threshold =
			(QOS_TX_LOW_VO_DEF * num_blocks) / 100;
		break;
	default:
		wl1251_error("Invalid TX queue id: %d", qid);
		return -EINVAL;
	}

	return 0;
}