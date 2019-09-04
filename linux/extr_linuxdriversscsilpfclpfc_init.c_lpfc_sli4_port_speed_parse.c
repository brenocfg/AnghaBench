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
typedef  int uint32_t ;
struct lpfc_hba {int dummy; } ;

/* Variables and functions */
#define  LPFC_ASYNC_LINK_SPEED_100MBPS 146 
#define  LPFC_ASYNC_LINK_SPEED_10GBPS 145 
#define  LPFC_ASYNC_LINK_SPEED_10MBPS 144 
#define  LPFC_ASYNC_LINK_SPEED_1GBPS 143 
#define  LPFC_ASYNC_LINK_SPEED_20GBPS 142 
#define  LPFC_ASYNC_LINK_SPEED_25GBPS 141 
#define  LPFC_ASYNC_LINK_SPEED_40GBPS 140 
#define  LPFC_ASYNC_LINK_SPEED_ZERO 139 
#define  LPFC_FC_LA_SPEED_10G 138 
#define  LPFC_FC_LA_SPEED_16G 137 
#define  LPFC_FC_LA_SPEED_1G 136 
#define  LPFC_FC_LA_SPEED_2G 135 
#define  LPFC_FC_LA_SPEED_32G 134 
#define  LPFC_FC_LA_SPEED_4G 133 
#define  LPFC_FC_LA_SPEED_64G 132 
#define  LPFC_FC_LA_SPEED_8G 131 
#define  LPFC_FC_LA_SPEED_UNKNOWN 130 
#define  LPFC_TRAILER_CODE_FC 129 
#define  LPFC_TRAILER_CODE_LINK 128 

__attribute__((used)) static uint32_t
lpfc_sli4_port_speed_parse(struct lpfc_hba *phba, uint32_t evt_code,
			   uint8_t speed_code)
{
	uint32_t port_speed;

	switch (evt_code) {
	case LPFC_TRAILER_CODE_LINK:
		switch (speed_code) {
		case LPFC_ASYNC_LINK_SPEED_ZERO:
			port_speed = 0;
			break;
		case LPFC_ASYNC_LINK_SPEED_10MBPS:
			port_speed = 10;
			break;
		case LPFC_ASYNC_LINK_SPEED_100MBPS:
			port_speed = 100;
			break;
		case LPFC_ASYNC_LINK_SPEED_1GBPS:
			port_speed = 1000;
			break;
		case LPFC_ASYNC_LINK_SPEED_10GBPS:
			port_speed = 10000;
			break;
		case LPFC_ASYNC_LINK_SPEED_20GBPS:
			port_speed = 20000;
			break;
		case LPFC_ASYNC_LINK_SPEED_25GBPS:
			port_speed = 25000;
			break;
		case LPFC_ASYNC_LINK_SPEED_40GBPS:
			port_speed = 40000;
			break;
		default:
			port_speed = 0;
		}
		break;
	case LPFC_TRAILER_CODE_FC:
		switch (speed_code) {
		case LPFC_FC_LA_SPEED_UNKNOWN:
			port_speed = 0;
			break;
		case LPFC_FC_LA_SPEED_1G:
			port_speed = 1000;
			break;
		case LPFC_FC_LA_SPEED_2G:
			port_speed = 2000;
			break;
		case LPFC_FC_LA_SPEED_4G:
			port_speed = 4000;
			break;
		case LPFC_FC_LA_SPEED_8G:
			port_speed = 8000;
			break;
		case LPFC_FC_LA_SPEED_10G:
			port_speed = 10000;
			break;
		case LPFC_FC_LA_SPEED_16G:
			port_speed = 16000;
			break;
		case LPFC_FC_LA_SPEED_32G:
			port_speed = 32000;
			break;
		case LPFC_FC_LA_SPEED_64G:
			port_speed = 64000;
			break;
		default:
			port_speed = 0;
		}
		break;
	default:
		port_speed = 0;
	}
	return port_speed;
}