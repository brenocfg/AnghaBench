#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t nrofbuffers; TYPE_1__** buffers; } ;
struct TYPE_6__ {scalar_t__ state; size_t primary_mixpos; int /*<<< orphan*/  lock; int /*<<< orphan*/  hwbuf; scalar_t__ buflen; } ;
typedef  size_t INT ;
typedef  TYPE_1__ IDirectSoundBufferImpl ;
typedef  TYPE_2__ DirectSoundDevice ;
typedef  size_t DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DSOUND_CheckEvent (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t DSOUND_MixOne (TYPE_1__*,size_t,size_t) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  RtlAcquireResourceShared (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  RtlReleaseResource (int /*<<< orphan*/ *) ; 
 scalar_t__ STATE_PLAYING ; 
 scalar_t__ STATE_STARTING ; 
 scalar_t__ STATE_STOPPED ; 
 scalar_t__ STATE_STOPPING ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 scalar_t__ TRUE ; 

__attribute__((used)) static DWORD DSOUND_MixToPrimary(const DirectSoundDevice *device, DWORD writepos, DWORD mixlen, BOOL recover, BOOL *all_stopped)
{
	INT i, len;
	DWORD minlen = 0;
	IDirectSoundBufferImpl	*dsb;

	/* unless we find a running buffer, all have stopped */
	*all_stopped = TRUE;

	TRACE("(%d,%d,%d)\n", writepos, mixlen, recover);
	for (i = 0; i < device->nrofbuffers; i++) {
		dsb = device->buffers[i];

		TRACE("MixToPrimary for %p, state=%d\n", dsb, dsb->state);

		if (dsb->buflen && dsb->state && !dsb->hwbuf) {
			TRACE("Checking %p, mixlen=%d\n", dsb, mixlen);
			RtlAcquireResourceShared(&dsb->lock, TRUE);
			/* if buffer is stopping it is stopped now */
			if (dsb->state == STATE_STOPPING) {
				dsb->state = STATE_STOPPED;
				DSOUND_CheckEvent(dsb, 0, 0);
			} else if (dsb->state != STATE_STOPPED) {

				/* if recovering, reset the mix position */
				if ((dsb->state == STATE_STARTING) || recover) {
					dsb->primary_mixpos = writepos;
				}

				/* if the buffer was starting, it must be playing now */
				if (dsb->state == STATE_STARTING)
					dsb->state = STATE_PLAYING;

				/* mix next buffer into the main buffer */
				len = DSOUND_MixOne(dsb, writepos, mixlen);

				if (!minlen) minlen = len;

				/* record the minimum length mixed from all buffers */
				/* we only want to return the length which *all* buffers have mixed */
				else if (len) minlen = (len < minlen) ? len : minlen;

				*all_stopped = FALSE;
			}
			RtlReleaseResource(&dsb->lock);
		}
	}

	TRACE("Mixed at least %d from all buffers\n", minlen);
	return minlen;
}