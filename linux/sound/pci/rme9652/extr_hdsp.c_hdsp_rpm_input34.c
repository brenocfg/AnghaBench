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
 int HDSP_RPM_Inp34 ; 
#define  HDSP_RPM_Inp34_Line_0dB 131 
#define  HDSP_RPM_Inp34_Line_n6dB 130 
#define  HDSP_RPM_Inp34_Phon_6dB 129 
#define  HDSP_RPM_Inp34_Phon_n6dB 128 

__attribute__((used)) static int hdsp_rpm_input34(struct hdsp *hdsp)
{
	switch (hdsp->control_register & HDSP_RPM_Inp34) {
	case HDSP_RPM_Inp34_Phon_6dB:
		return 0;
	case HDSP_RPM_Inp34_Phon_n6dB:
		return 2;
	case HDSP_RPM_Inp34_Line_0dB:
		return 3;
	case HDSP_RPM_Inp34_Line_n6dB:
		return 4;
	}
	return 1;
}