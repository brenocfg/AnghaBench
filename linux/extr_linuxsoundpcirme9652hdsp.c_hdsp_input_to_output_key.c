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
struct hdsp {int io_type; int firmware_rev; } ;

/* Variables and functions */
#define  Digiface 132 
#define  H9632 131 
#define  H9652 130 
#define  Multiface 129 
#define  RPM 128 

__attribute__((used)) static int hdsp_input_to_output_key (struct hdsp *hdsp, int in, int out)
{
	switch (hdsp->io_type) {
	case Multiface:
	case Digiface:
	case RPM:
	default:
		if (hdsp->firmware_rev == 0xa)
			return (64 * out) + in;
		else
			return (52 * out) + in;
	case H9632:
		return (32 * out) + in;
	case H9652:
		return (52 * out) + in;
	}
}