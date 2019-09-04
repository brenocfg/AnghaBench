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
struct TYPE_6__ {int protocol; } ;
struct TYPE_7__ {int m_stream_id; TYPE_1__ Link; int /*<<< orphan*/  m_bPlaying; } ;
typedef  TYPE_2__ RTMP ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int RTMP_FEATURE_WRITE ; 
 int /*<<< orphan*/  SendDeleteStream (TYPE_2__*,int) ; 
 int /*<<< orphan*/  SendFCUnpublish (TYPE_2__*,int) ; 

void
RTMP_DeleteStream(RTMP *r, int streamIdx)
{
    if (r->m_stream_id < 0)
        return;

    r->m_bPlaying = FALSE;

    if ((r->Link.protocol & RTMP_FEATURE_WRITE))
        SendFCUnpublish(r, streamIdx);

    SendDeleteStream(r, r->m_stream_id);
    r->m_stream_id = -1;
}