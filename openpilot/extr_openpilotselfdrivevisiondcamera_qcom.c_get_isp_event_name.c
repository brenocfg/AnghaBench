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

/* Variables and functions */
#define  ISP_EVENT_BUF_DIVERT 148 
#define  ISP_EVENT_BUF_DONE 147 
#define  ISP_EVENT_BUF_FATAL_ERROR 146 
#define  ISP_EVENT_COMP_STATS_NOTIFY 145 
#define  ISP_EVENT_EOF 144 
#define  ISP_EVENT_EPOCH_0 143 
#define  ISP_EVENT_EPOCH_1 142 
#define  ISP_EVENT_ERROR 141 
#define  ISP_EVENT_FE_READ_DONE 140 
#define  ISP_EVENT_HW_FATAL_ERROR 139 
#define  ISP_EVENT_IOMMU_P_FAULT 138 
#define  ISP_EVENT_IRQ_VIOLATION 137 
#define  ISP_EVENT_PING_PONG_MISMATCH 136 
#define  ISP_EVENT_REG_UPDATE 135 
#define  ISP_EVENT_REG_UPDATE_MISSING 134 
#define  ISP_EVENT_SOF 133 
#define  ISP_EVENT_START_ACK 132 
#define  ISP_EVENT_STATS_NOTIFY 131 
#define  ISP_EVENT_STATS_OVERFLOW 130 
#define  ISP_EVENT_STOP_ACK 129 
#define  ISP_EVENT_STREAM_UPDATE_DONE 128 

const char* get_isp_event_name(unsigned int type) {
  switch (type) {
  case ISP_EVENT_REG_UPDATE: return "ISP_EVENT_REG_UPDATE";
  case ISP_EVENT_EPOCH_0: return "ISP_EVENT_EPOCH_0";
  case ISP_EVENT_EPOCH_1: return "ISP_EVENT_EPOCH_1";
  case ISP_EVENT_START_ACK: return "ISP_EVENT_START_ACK";
  case ISP_EVENT_STOP_ACK: return "ISP_EVENT_STOP_ACK";
  case ISP_EVENT_IRQ_VIOLATION: return "ISP_EVENT_IRQ_VIOLATION";
  case ISP_EVENT_STATS_OVERFLOW: return "ISP_EVENT_STATS_OVERFLOW";
  case ISP_EVENT_ERROR: return "ISP_EVENT_ERROR";
  case ISP_EVENT_SOF: return "ISP_EVENT_SOF";
  case ISP_EVENT_EOF: return "ISP_EVENT_EOF";
  case ISP_EVENT_BUF_DONE: return "ISP_EVENT_BUF_DONE";
  case ISP_EVENT_BUF_DIVERT: return "ISP_EVENT_BUF_DIVERT";
  case ISP_EVENT_STATS_NOTIFY: return "ISP_EVENT_STATS_NOTIFY";
  case ISP_EVENT_COMP_STATS_NOTIFY: return "ISP_EVENT_COMP_STATS_NOTIFY";
  case ISP_EVENT_FE_READ_DONE: return "ISP_EVENT_FE_READ_DONE";
  case ISP_EVENT_IOMMU_P_FAULT: return "ISP_EVENT_IOMMU_P_FAULT";
  case ISP_EVENT_HW_FATAL_ERROR: return "ISP_EVENT_HW_FATAL_ERROR";
  case ISP_EVENT_PING_PONG_MISMATCH: return "ISP_EVENT_PING_PONG_MISMATCH";
  case ISP_EVENT_REG_UPDATE_MISSING: return "ISP_EVENT_REG_UPDATE_MISSING";
  case ISP_EVENT_BUF_FATAL_ERROR: return "ISP_EVENT_BUF_FATAL_ERROR";
  case ISP_EVENT_STREAM_UPDATE_DONE: return "ISP_EVENT_STREAM_UPDATE_DONE";
  default: return "unknown";
  }
}