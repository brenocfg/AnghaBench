#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pcxhr_mgr {TYPE_1__* pci; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int PCXHR_INPL (struct pcxhr_mgr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCXHR_PLX_MBOX2 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static inline int pcxhr_pipes_running(struct pcxhr_mgr *mgr)
{
	int start_mask = PCXHR_INPL(mgr, PCXHR_PLX_MBOX2);
	/* least segnificant 12 bits are the pipe states
	 * for the playback audios
	 * next 12 bits are the pipe states for the capture audios
	 * (PCXHR_PIPE_STATE_CAPTURE_OFFSET)
	 */
	start_mask &= 0xffffff;
	dev_dbg(&mgr->pci->dev, "CMD_PIPE_STATE MBOX2=0x%06x\n", start_mask);
	return start_mask;
}