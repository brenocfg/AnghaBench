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
#define  ISP1362_INT_ATL 137 
#define  ISP1362_INT_CLKRDY 136 
#define  ISP1362_INT_EOT 135 
#define  ISP1362_INT_INTL 134 
#define  ISP1362_INT_ISTL0 133 
#define  ISP1362_INT_ISTL1 132 
#define  ISP1362_INT_OPR 131 
#define  ISP1362_INT_OTG 130 
#define  ISP1362_INT_SOF 129 
#define  ISP1362_INT_SUSP 128 

__attribute__((used)) static inline const char *ISP1362_INT_NAME(int n)
{
	switch (n) {
	case ISP1362_INT_SOF:    return "SOF";
	case ISP1362_INT_ISTL0:  return "ISTL0";
	case ISP1362_INT_ISTL1:  return "ISTL1";
	case ISP1362_INT_EOT:    return "EOT";
	case ISP1362_INT_OPR:    return "OPR";
	case ISP1362_INT_SUSP:   return "SUSP";
	case ISP1362_INT_CLKRDY: return "CLKRDY";
	case ISP1362_INT_INTL:   return "INTL";
	case ISP1362_INT_ATL:    return "ATL";
	case ISP1362_INT_OTG:    return "OTG";
	default:                 return "unknown";
	}
}