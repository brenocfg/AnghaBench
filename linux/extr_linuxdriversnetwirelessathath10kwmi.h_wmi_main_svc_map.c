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
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  SVCMAP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  WMI_MAIN_SERVICE_11AC ; 
 int /*<<< orphan*/  WMI_MAIN_SERVICE_AP_DFS ; 
 int /*<<< orphan*/  WMI_MAIN_SERVICE_AP_UAPSD ; 
 int /*<<< orphan*/  WMI_MAIN_SERVICE_ARPNS_OFFLOAD ; 
 int /*<<< orphan*/  WMI_MAIN_SERVICE_BCN_FILTER ; 
 int /*<<< orphan*/  WMI_MAIN_SERVICE_BCN_MISS_OFFLOAD ; 
 int /*<<< orphan*/  WMI_MAIN_SERVICE_BEACON_OFFLOAD ; 
 int /*<<< orphan*/  WMI_MAIN_SERVICE_BLOCKACK ; 
 int /*<<< orphan*/  WMI_MAIN_SERVICE_CHATTER ; 
 int /*<<< orphan*/  WMI_MAIN_SERVICE_COEX_FREQAVOID ; 
 int /*<<< orphan*/  WMI_MAIN_SERVICE_CSA_OFFLOAD ; 
 int /*<<< orphan*/  WMI_MAIN_SERVICE_FORCE_FW_HANG ; 
 int /*<<< orphan*/  WMI_MAIN_SERVICE_GPIO ; 
 int /*<<< orphan*/  WMI_MAIN_SERVICE_GTK_OFFLOAD ; 
 int /*<<< orphan*/  WMI_MAIN_SERVICE_IRAM_TIDS ; 
 int /*<<< orphan*/  WMI_MAIN_SERVICE_NLO ; 
 int /*<<< orphan*/  WMI_MAIN_SERVICE_PACKET_POWER_SAVE ; 
 int /*<<< orphan*/  WMI_MAIN_SERVICE_PHYERR ; 
 int /*<<< orphan*/  WMI_MAIN_SERVICE_RATECTRL ; 
 int /*<<< orphan*/  WMI_MAIN_SERVICE_RATECTRL_CACHE ; 
 int /*<<< orphan*/  WMI_MAIN_SERVICE_ROAM_OFFLOAD ; 
 int /*<<< orphan*/  WMI_MAIN_SERVICE_RTT ; 
 int /*<<< orphan*/  WMI_MAIN_SERVICE_SCAN_OFFLOAD ; 
 int /*<<< orphan*/  WMI_MAIN_SERVICE_SCAN_SCH ; 
 int /*<<< orphan*/  WMI_MAIN_SERVICE_STA_ADVANCED_PWRSAVE ; 
 int /*<<< orphan*/  WMI_MAIN_SERVICE_STA_DTIM_PS_MODULATED_DTIM ; 
 int /*<<< orphan*/  WMI_MAIN_SERVICE_STA_KEEP_ALIVE ; 
 int /*<<< orphan*/  WMI_MAIN_SERVICE_STA_PWRSAVE ; 
 int /*<<< orphan*/  WMI_MAIN_SERVICE_STA_UAPSD_BASIC_AUTO_TRIG ; 
 int /*<<< orphan*/  WMI_MAIN_SERVICE_STA_UAPSD_VAR_AUTO_TRIG ; 
 int /*<<< orphan*/  WMI_MAIN_SERVICE_TX_ENCAP ; 
 int /*<<< orphan*/  WMI_MAIN_SERVICE_WOW ; 
 int /*<<< orphan*/  WMI_SERVICE_11AC ; 
 int /*<<< orphan*/  WMI_SERVICE_AP_DFS ; 
 int /*<<< orphan*/  WMI_SERVICE_AP_UAPSD ; 
 int /*<<< orphan*/  WMI_SERVICE_ARPNS_OFFLOAD ; 
 int /*<<< orphan*/  WMI_SERVICE_BCN_FILTER ; 
 int /*<<< orphan*/  WMI_SERVICE_BCN_MISS_OFFLOAD ; 
 int /*<<< orphan*/  WMI_SERVICE_BEACON_OFFLOAD ; 
 int /*<<< orphan*/  WMI_SERVICE_BLOCKACK ; 
 int /*<<< orphan*/  WMI_SERVICE_CHATTER ; 
 int /*<<< orphan*/  WMI_SERVICE_COEX_FREQAVOID ; 
 int /*<<< orphan*/  WMI_SERVICE_CSA_OFFLOAD ; 
 int /*<<< orphan*/  WMI_SERVICE_FORCE_FW_HANG ; 
 int /*<<< orphan*/  WMI_SERVICE_GPIO ; 
 int /*<<< orphan*/  WMI_SERVICE_GTK_OFFLOAD ; 
 int /*<<< orphan*/  WMI_SERVICE_IRAM_TIDS ; 
 int /*<<< orphan*/  WMI_SERVICE_NLO ; 
 int /*<<< orphan*/  WMI_SERVICE_PACKET_POWER_SAVE ; 
 int /*<<< orphan*/  WMI_SERVICE_PHYERR ; 
 int /*<<< orphan*/  WMI_SERVICE_RATECTRL ; 
 int /*<<< orphan*/  WMI_SERVICE_RATECTRL_CACHE ; 
 int /*<<< orphan*/  WMI_SERVICE_ROAM_OFFLOAD ; 
 int /*<<< orphan*/  WMI_SERVICE_RTT ; 
 int /*<<< orphan*/  WMI_SERVICE_SCAN_OFFLOAD ; 
 int /*<<< orphan*/  WMI_SERVICE_SCAN_SCH ; 
 int /*<<< orphan*/  WMI_SERVICE_STA_ADVANCED_PWRSAVE ; 
 int /*<<< orphan*/  WMI_SERVICE_STA_DTIM_PS_MODULATED_DTIM ; 
 int /*<<< orphan*/  WMI_SERVICE_STA_KEEP_ALIVE ; 
 int /*<<< orphan*/  WMI_SERVICE_STA_PWRSAVE ; 
 int /*<<< orphan*/  WMI_SERVICE_STA_UAPSD_BASIC_AUTO_TRIG ; 
 int /*<<< orphan*/  WMI_SERVICE_STA_UAPSD_VAR_AUTO_TRIG ; 
 int /*<<< orphan*/  WMI_SERVICE_TX_ENCAP ; 
 int /*<<< orphan*/  WMI_SERVICE_WOW ; 

__attribute__((used)) static inline void wmi_main_svc_map(const __le32 *in, unsigned long *out,
				    size_t len)
{
	SVCMAP(WMI_MAIN_SERVICE_BEACON_OFFLOAD,
	       WMI_SERVICE_BEACON_OFFLOAD, len);
	SVCMAP(WMI_MAIN_SERVICE_SCAN_OFFLOAD,
	       WMI_SERVICE_SCAN_OFFLOAD, len);
	SVCMAP(WMI_MAIN_SERVICE_ROAM_OFFLOAD,
	       WMI_SERVICE_ROAM_OFFLOAD, len);
	SVCMAP(WMI_MAIN_SERVICE_BCN_MISS_OFFLOAD,
	       WMI_SERVICE_BCN_MISS_OFFLOAD, len);
	SVCMAP(WMI_MAIN_SERVICE_STA_PWRSAVE,
	       WMI_SERVICE_STA_PWRSAVE, len);
	SVCMAP(WMI_MAIN_SERVICE_STA_ADVANCED_PWRSAVE,
	       WMI_SERVICE_STA_ADVANCED_PWRSAVE, len);
	SVCMAP(WMI_MAIN_SERVICE_AP_UAPSD,
	       WMI_SERVICE_AP_UAPSD, len);
	SVCMAP(WMI_MAIN_SERVICE_AP_DFS,
	       WMI_SERVICE_AP_DFS, len);
	SVCMAP(WMI_MAIN_SERVICE_11AC,
	       WMI_SERVICE_11AC, len);
	SVCMAP(WMI_MAIN_SERVICE_BLOCKACK,
	       WMI_SERVICE_BLOCKACK, len);
	SVCMAP(WMI_MAIN_SERVICE_PHYERR,
	       WMI_SERVICE_PHYERR, len);
	SVCMAP(WMI_MAIN_SERVICE_BCN_FILTER,
	       WMI_SERVICE_BCN_FILTER, len);
	SVCMAP(WMI_MAIN_SERVICE_RTT,
	       WMI_SERVICE_RTT, len);
	SVCMAP(WMI_MAIN_SERVICE_RATECTRL,
	       WMI_SERVICE_RATECTRL, len);
	SVCMAP(WMI_MAIN_SERVICE_WOW,
	       WMI_SERVICE_WOW, len);
	SVCMAP(WMI_MAIN_SERVICE_RATECTRL_CACHE,
	       WMI_SERVICE_RATECTRL_CACHE, len);
	SVCMAP(WMI_MAIN_SERVICE_IRAM_TIDS,
	       WMI_SERVICE_IRAM_TIDS, len);
	SVCMAP(WMI_MAIN_SERVICE_ARPNS_OFFLOAD,
	       WMI_SERVICE_ARPNS_OFFLOAD, len);
	SVCMAP(WMI_MAIN_SERVICE_NLO,
	       WMI_SERVICE_NLO, len);
	SVCMAP(WMI_MAIN_SERVICE_GTK_OFFLOAD,
	       WMI_SERVICE_GTK_OFFLOAD, len);
	SVCMAP(WMI_MAIN_SERVICE_SCAN_SCH,
	       WMI_SERVICE_SCAN_SCH, len);
	SVCMAP(WMI_MAIN_SERVICE_CSA_OFFLOAD,
	       WMI_SERVICE_CSA_OFFLOAD, len);
	SVCMAP(WMI_MAIN_SERVICE_CHATTER,
	       WMI_SERVICE_CHATTER, len);
	SVCMAP(WMI_MAIN_SERVICE_COEX_FREQAVOID,
	       WMI_SERVICE_COEX_FREQAVOID, len);
	SVCMAP(WMI_MAIN_SERVICE_PACKET_POWER_SAVE,
	       WMI_SERVICE_PACKET_POWER_SAVE, len);
	SVCMAP(WMI_MAIN_SERVICE_FORCE_FW_HANG,
	       WMI_SERVICE_FORCE_FW_HANG, len);
	SVCMAP(WMI_MAIN_SERVICE_GPIO,
	       WMI_SERVICE_GPIO, len);
	SVCMAP(WMI_MAIN_SERVICE_STA_DTIM_PS_MODULATED_DTIM,
	       WMI_SERVICE_STA_DTIM_PS_MODULATED_DTIM, len);
	SVCMAP(WMI_MAIN_SERVICE_STA_UAPSD_BASIC_AUTO_TRIG,
	       WMI_SERVICE_STA_UAPSD_BASIC_AUTO_TRIG, len);
	SVCMAP(WMI_MAIN_SERVICE_STA_UAPSD_VAR_AUTO_TRIG,
	       WMI_SERVICE_STA_UAPSD_VAR_AUTO_TRIG, len);
	SVCMAP(WMI_MAIN_SERVICE_STA_KEEP_ALIVE,
	       WMI_SERVICE_STA_KEEP_ALIVE, len);
	SVCMAP(WMI_MAIN_SERVICE_TX_ENCAP,
	       WMI_SERVICE_TX_ENCAP, len);
}