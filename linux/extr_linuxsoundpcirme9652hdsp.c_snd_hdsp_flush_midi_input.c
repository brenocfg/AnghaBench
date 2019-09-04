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
 scalar_t__ snd_hdsp_midi_input_available (struct hdsp*,int) ; 
 int /*<<< orphan*/  snd_hdsp_midi_read_byte (struct hdsp*,int) ; 

__attribute__((used)) static void snd_hdsp_flush_midi_input (struct hdsp *hdsp, int id)
{
	while (snd_hdsp_midi_input_available (hdsp, id))
		snd_hdsp_midi_read_byte (hdsp, id);
}