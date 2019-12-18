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
 int /*<<< orphan*/  HDSP_midiStatusIn0 ; 
 int /*<<< orphan*/  HDSP_midiStatusIn1 ; 
 int hdsp_read (struct hdsp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_hdsp_midi_input_available (struct hdsp *hdsp, int id)
{
	if (id)
		return (hdsp_read(hdsp, HDSP_midiStatusIn1) & 0xff);
	else
		return (hdsp_read(hdsp, HDSP_midiStatusIn0) & 0xff);
}