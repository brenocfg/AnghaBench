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
struct hdsp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDSP_midiDataIn0 ; 
 int /*<<< orphan*/  HDSP_midiDataIn1 ; 
 unsigned char hdsp_read (struct hdsp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned char snd_hdsp_midi_read_byte (struct hdsp *hdsp, int id)
{
	/* the hardware already does the relevant bit-mask with 0xff */
	if (id)
		return hdsp_read(hdsp, HDSP_midiDataIn1);
	else
		return hdsp_read(hdsp, HDSP_midiDataIn0);
}