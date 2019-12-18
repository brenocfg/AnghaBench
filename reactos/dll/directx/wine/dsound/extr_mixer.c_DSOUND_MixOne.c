#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int buf_mixpos; int primary_mixpos; int playflags; int tmp_buffer_len; scalar_t__ state; TYPE_1__* device; int /*<<< orphan*/  buflen; int /*<<< orphan*/  sec_mixpos; scalar_t__ leadin; } ;
struct TYPE_5__ {int fraglen; int buflen; } ;
typedef  TYPE_2__ IDirectSoundBufferImpl ;
typedef  int DWORD ;

/* Variables and functions */
 int DSBPLAY_LOOPING ; 
 int DSOUND_BufPtrDiff (int,int,int) ; 
 int DSOUND_MixInBuffer (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  ERR (char*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ FALSE ; 
 scalar_t__ STATE_STARTING ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 

__attribute__((used)) static DWORD DSOUND_MixOne(IDirectSoundBufferImpl *dsb, DWORD writepos, DWORD mixlen)
{
	/* The buffer's primary_mixpos may be before or after the device
	 * buffer's mixpos, but both must be ahead of writepos. */
	DWORD primary_done;

	TRACE("(%p,%d,%d)\n",dsb,writepos,mixlen);
	TRACE("writepos=%d, buf_mixpos=%d, primary_mixpos=%d, mixlen=%d\n", writepos, dsb->buf_mixpos, dsb->primary_mixpos, mixlen);
	TRACE("looping=%d, leadin=%d, buflen=%d\n", dsb->playflags, dsb->leadin, dsb->tmp_buffer_len);

	/* If leading in, only mix about 20 ms, and 'skip' mixing the rest, for more fluid pointer advancement */
	if (dsb->leadin && dsb->state == STATE_STARTING)
	{
		if (mixlen > 2 * dsb->device->fraglen)
		{
			dsb->primary_mixpos += mixlen - 2 * dsb->device->fraglen;
			dsb->primary_mixpos %= dsb->device->buflen;
		}
	}
	dsb->leadin = FALSE;

	/* calculate how much pre-buffering has already been done for this buffer */
	primary_done = DSOUND_BufPtrDiff(dsb->device->buflen, dsb->primary_mixpos, writepos);

	/* sanity */
	if(mixlen < primary_done)
	{
		/* Should *NEVER* happen */
		ERR("Fatal error. Under/Overflow? primary_done=%d, mixpos=%d/%d (%d/%d), primary_mixpos=%d, writepos=%d, mixlen=%d\n", primary_done,dsb->buf_mixpos,dsb->tmp_buffer_len,dsb->sec_mixpos, dsb->buflen, dsb->primary_mixpos, writepos, mixlen);
		dsb->primary_mixpos = writepos + mixlen;
		dsb->primary_mixpos %= dsb->device->buflen;
		return mixlen;
	}

	/* take into account already mixed data */
	mixlen -= primary_done;

	TRACE("primary_done=%d, mixlen (primary) = %i\n", primary_done, mixlen);

	if (!mixlen)
		return primary_done;

	/* First try to mix to the end of the buffer if possible
	 * Theoretically it would allow for better optimization
	*/
	if (mixlen + dsb->buf_mixpos >= dsb->tmp_buffer_len)
	{
		DWORD newmixed, mixfirst = dsb->tmp_buffer_len - dsb->buf_mixpos;
		newmixed = DSOUND_MixInBuffer(dsb, dsb->primary_mixpos, mixfirst);
		mixlen -= newmixed;

		if (dsb->playflags & DSBPLAY_LOOPING)
			while (newmixed && mixlen)
			{
				mixfirst = (dsb->tmp_buffer_len < mixlen ? dsb->tmp_buffer_len : mixlen);
				newmixed = DSOUND_MixInBuffer(dsb, dsb->primary_mixpos, mixfirst);
				mixlen -= newmixed;
			}
	}
	else DSOUND_MixInBuffer(dsb, dsb->primary_mixpos, mixlen);

	/* re-calculate the primary done */
	primary_done = DSOUND_BufPtrDiff(dsb->device->buflen, dsb->primary_mixpos, writepos);

	TRACE("new primary_mixpos=%d, total mixed data=%d\n", dsb->primary_mixpos, primary_done);

	/* Report back the total prebuffered amount for this buffer */
	return primary_done;
}