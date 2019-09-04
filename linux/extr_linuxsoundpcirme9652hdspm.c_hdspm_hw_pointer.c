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
struct hdspm {int io_type; int period_bytes; } ;
typedef  int snd_pcm_uframes_t ;

/* Variables and functions */
#define  AIO 129 
 int HDSPM_BufferID ; 
 int HDSPM_BufferPositionMask ; 
 int /*<<< orphan*/  HDSPM_statusRegister ; 
#define  RayDAT 128 
 int hdspm_read (struct hdspm*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static snd_pcm_uframes_t hdspm_hw_pointer(struct hdspm *hdspm)
{
	int position;

	position = hdspm_read(hdspm, HDSPM_statusRegister);

	switch (hdspm->io_type) {
	case RayDAT:
	case AIO:
		position &= HDSPM_BufferPositionMask;
		position /= 4; /* Bytes per sample */
		break;
	default:
		position = (position & HDSPM_BufferID) ?
			(hdspm->period_bytes / 4) : 0;
	}

	return position;
}