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
struct hdsp {int period_bytes; int /*<<< orphan*/  precise_ptr; } ;
typedef  int snd_pcm_uframes_t ;

/* Variables and functions */
 int HDSP_BufferID ; 
 int HDSP_BufferPositionMask ; 
 int /*<<< orphan*/  HDSP_statusRegister ; 
 int hdsp_read (struct hdsp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static snd_pcm_uframes_t hdsp_hw_pointer(struct hdsp *hdsp)
{
	int position;

	position = hdsp_read(hdsp, HDSP_statusRegister);

	if (!hdsp->precise_ptr)
		return (position & HDSP_BufferID) ? (hdsp->period_bytes / 4) : 0;

	position &= HDSP_BufferPositionMask;
	position /= 4;
	position &= (hdsp->period_bytes/2) - 1;
	return position;
}