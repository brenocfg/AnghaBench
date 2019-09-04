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
 int const DCCP_NR_PKT_TYPES ; 
#define  DCCP_PKT_ACK 137 
#define  DCCP_PKT_CLOSE 136 
#define  DCCP_PKT_CLOSEREQ 135 
#define  DCCP_PKT_DATA 134 
#define  DCCP_PKT_DATAACK 133 
#define  DCCP_PKT_REQUEST 132 
#define  DCCP_PKT_RESET 131 
#define  DCCP_PKT_RESPONSE 130 
#define  DCCP_PKT_SYNC 129 
#define  DCCP_PKT_SYNCACK 128 

const char *dccp_packet_name(const int type)
{
	static const char *const dccp_packet_names[] = {
		[DCCP_PKT_REQUEST]  = "REQUEST",
		[DCCP_PKT_RESPONSE] = "RESPONSE",
		[DCCP_PKT_DATA]	    = "DATA",
		[DCCP_PKT_ACK]	    = "ACK",
		[DCCP_PKT_DATAACK]  = "DATAACK",
		[DCCP_PKT_CLOSEREQ] = "CLOSEREQ",
		[DCCP_PKT_CLOSE]    = "CLOSE",
		[DCCP_PKT_RESET]    = "RESET",
		[DCCP_PKT_SYNC]	    = "SYNC",
		[DCCP_PKT_SYNCACK]  = "SYNCACK",
	};

	if (type >= DCCP_NR_PKT_TYPES)
		return "INVALID";
	else
		return dccp_packet_names[type];
}