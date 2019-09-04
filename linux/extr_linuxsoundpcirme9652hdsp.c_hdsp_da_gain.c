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
struct hdsp {int control_register; } ;

/* Variables and functions */
#define  HDSP_DAGainHighGain 130 
 int HDSP_DAGainMask ; 
#define  HDSP_DAGainMinus10dBV 129 
#define  HDSP_DAGainPlus4dBu 128 

__attribute__((used)) static int hdsp_da_gain(struct hdsp *hdsp)
{
	switch (hdsp->control_register & HDSP_DAGainMask) {
	case HDSP_DAGainHighGain:
		return 0;
	case HDSP_DAGainPlus4dBu:
		return 1;
	case HDSP_DAGainMinus10dBV:
		return 2;
	default:
		return 1;
	}
}