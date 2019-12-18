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
 int HDSP_AudioInterruptEnable ; 
 int HDSP_Start ; 
 int /*<<< orphan*/  HDSP_controlRegister ; 
 int /*<<< orphan*/  hdsp_write (struct hdsp*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hdsp_start_audio(struct hdsp *s)
{
	s->control_register |= (HDSP_AudioInterruptEnable | HDSP_Start);
	hdsp_write(s, HDSP_controlRegister, s->control_register);
}