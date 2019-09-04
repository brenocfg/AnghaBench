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
typedef  enum ath10k_htc_svc_id { ____Placeholder_ath10k_htc_svc_id } ath10k_htc_svc_id ;

/* Variables and functions */
#define  ATH10K_HTC_SVC_ID_HTT_DATA2_MSG 141 
#define  ATH10K_HTC_SVC_ID_HTT_DATA3_MSG 140 
#define  ATH10K_HTC_SVC_ID_HTT_DATA_MSG 139 
#define  ATH10K_HTC_SVC_ID_HTT_LOG_MSG 138 
#define  ATH10K_HTC_SVC_ID_NMI_CONTROL 137 
#define  ATH10K_HTC_SVC_ID_NMI_DATA 136 
#define  ATH10K_HTC_SVC_ID_RESERVED 135 
#define  ATH10K_HTC_SVC_ID_RSVD_CTRL 134 
#define  ATH10K_HTC_SVC_ID_TEST_RAW_STREAMS 133 
#define  ATH10K_HTC_SVC_ID_WMI_CONTROL 132 
#define  ATH10K_HTC_SVC_ID_WMI_DATA_BE 131 
#define  ATH10K_HTC_SVC_ID_WMI_DATA_BK 130 
#define  ATH10K_HTC_SVC_ID_WMI_DATA_VI 129 
#define  ATH10K_HTC_SVC_ID_WMI_DATA_VO 128 

__attribute__((used)) static const char *htc_service_name(enum ath10k_htc_svc_id id)
{
	switch (id) {
	case ATH10K_HTC_SVC_ID_RESERVED:
		return "Reserved";
	case ATH10K_HTC_SVC_ID_RSVD_CTRL:
		return "Control";
	case ATH10K_HTC_SVC_ID_WMI_CONTROL:
		return "WMI";
	case ATH10K_HTC_SVC_ID_WMI_DATA_BE:
		return "DATA BE";
	case ATH10K_HTC_SVC_ID_WMI_DATA_BK:
		return "DATA BK";
	case ATH10K_HTC_SVC_ID_WMI_DATA_VI:
		return "DATA VI";
	case ATH10K_HTC_SVC_ID_WMI_DATA_VO:
		return "DATA VO";
	case ATH10K_HTC_SVC_ID_NMI_CONTROL:
		return "NMI Control";
	case ATH10K_HTC_SVC_ID_NMI_DATA:
		return "NMI Data";
	case ATH10K_HTC_SVC_ID_HTT_DATA_MSG:
		return "HTT Data";
	case ATH10K_HTC_SVC_ID_HTT_DATA2_MSG:
		return "HTT Data";
	case ATH10K_HTC_SVC_ID_HTT_DATA3_MSG:
		return "HTT Data";
	case ATH10K_HTC_SVC_ID_TEST_RAW_STREAMS:
		return "RAW";
	case ATH10K_HTC_SVC_ID_HTT_LOG_MSG:
		return "PKTLOG";
	}

	return "Unknown";
}