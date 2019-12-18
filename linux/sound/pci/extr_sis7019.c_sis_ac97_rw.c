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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct sis7019 {unsigned long ioport; TYPE_1__* pci; int /*<<< orphan*/  ac97_mutex; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ SIS_AC97_CMD ; 
 scalar_t__ SIS_AC97_SEMA ; 
 int SIS_AC97_SEMA_BUSY ; 
 int /*<<< orphan*/  SIS_AC97_SEMA_RELEASE ; 
 scalar_t__ SIS_AC97_STATUS ; 
 int SIS_AC97_STATUS_BUSY ; 
#define  SIS_AC97_STATUS_CODEC2_READY 130 
#define  SIS_AC97_STATUS_CODEC3_READY 129 
#define  SIS_AC97_STATUS_CODEC_READY 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int inl (scalar_t__) ; 
 int inw (scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static unsigned short sis_ac97_rw(struct sis7019 *sis, int codec, u32 cmd)
{
	unsigned long io = sis->ioport;
	unsigned short val = 0xffff;
	u16 status;
	u16 rdy;
	int count;
	static const u16 codec_ready[3] = {
		SIS_AC97_STATUS_CODEC_READY,
		SIS_AC97_STATUS_CODEC2_READY,
		SIS_AC97_STATUS_CODEC3_READY,
	};

	rdy = codec_ready[codec];


	/* Get the AC97 semaphore -- software first, so we don't spin
	 * pounding out IO reads on the hardware semaphore...
	 */
	mutex_lock(&sis->ac97_mutex);

	count = 0xffff;
	while ((inw(io + SIS_AC97_SEMA) & SIS_AC97_SEMA_BUSY) && --count)
		udelay(1);

	if (!count)
		goto timeout;

	/* ... and wait for any outstanding commands to complete ...
	 */
	count = 0xffff;
	do {
		status = inw(io + SIS_AC97_STATUS);
		if ((status & rdy) && !(status & SIS_AC97_STATUS_BUSY))
			break;

		udelay(1);
	} while (--count);

	if (!count)
		goto timeout_sema;

	/* ... before sending our command and waiting for it to finish ...
	 */
	outl(cmd, io + SIS_AC97_CMD);
	udelay(10);

	count = 0xffff;
	while ((inw(io + SIS_AC97_STATUS) & SIS_AC97_STATUS_BUSY) && --count)
		udelay(1);

	/* ... and reading the results (if any).
	 */
	val = inl(io + SIS_AC97_CMD) >> 16;

timeout_sema:
	outl(SIS_AC97_SEMA_RELEASE, io + SIS_AC97_SEMA);
timeout:
	mutex_unlock(&sis->ac97_mutex);

	if (!count) {
		dev_err(&sis->pci->dev, "ac97 codec %d timeout cmd 0x%08x\n",
					codec, cmd);
	}

	return val;
}