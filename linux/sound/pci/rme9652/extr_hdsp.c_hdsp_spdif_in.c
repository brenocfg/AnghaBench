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
 int HDSP_SPDIFInputMask ; 
 unsigned int hdsp_decode_spdif_in (int) ; 

__attribute__((used)) static unsigned int hdsp_spdif_in(struct hdsp *hdsp)
{
	return hdsp_decode_spdif_in(hdsp->control_register & HDSP_SPDIFInputMask);
}