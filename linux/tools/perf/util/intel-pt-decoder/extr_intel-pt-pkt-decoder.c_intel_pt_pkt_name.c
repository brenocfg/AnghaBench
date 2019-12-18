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
typedef  enum intel_pt_pkt_type { ____Placeholder_intel_pt_pkt_type } intel_pt_pkt_type ;

/* Variables and functions */
 char const** packet_name ; 

const char *intel_pt_pkt_name(enum intel_pt_pkt_type type)
{
	return packet_name[type];
}