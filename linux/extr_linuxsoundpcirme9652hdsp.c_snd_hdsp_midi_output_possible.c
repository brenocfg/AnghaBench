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
 int /*<<< orphan*/  HDSP_midiStatusOut0 ; 
 int /*<<< orphan*/  HDSP_midiStatusOut1 ; 
 int hdsp_read (struct hdsp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_hdsp_midi_output_possible (struct hdsp *hdsp, int id)
{
	int fifo_bytes_used;

	if (id)
		fifo_bytes_used = hdsp_read(hdsp, HDSP_midiStatusOut1) & 0xff;
	else
		fifo_bytes_used = hdsp_read(hdsp, HDSP_midiStatusOut0) & 0xff;

	if (fifo_bytes_used < 128)
		return  128 - fifo_bytes_used;
	else
		return 0;
}