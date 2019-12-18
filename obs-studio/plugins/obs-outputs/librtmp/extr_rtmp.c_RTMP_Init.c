#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int timeout; int swfAge; scalar_t__ nStreams; scalar_t__ curStreamIdx; } ;
struct TYPE_6__ {int sb_socket; } ;
struct TYPE_8__ {int m_bSendChunkSizeInfo; int m_nBufferMS; int m_nClientBW; int m_nClientBW2; int m_nServerBW; double m_fAudioCodecs; double m_fVideoCodecs; TYPE_2__ Link; void* m_outChunkSize; void* m_inChunkSize; TYPE_1__ m_sb; } ;
typedef  TYPE_3__ RTMP ;

/* Variables and functions */
 void* RTMP_DEFAULT_CHUNKSIZE ; 
 int /*<<< orphan*/  RTMP_TLS_Init () ; 
 int /*<<< orphan*/  RTMP_TLS_ctx ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

void
RTMP_Init(RTMP *r)
{
#ifdef CRYPTO
    if (!RTMP_TLS_ctx)
        RTMP_TLS_Init();
#endif

    memset(r, 0, sizeof(RTMP));
    r->m_sb.sb_socket = -1;
    r->m_inChunkSize = RTMP_DEFAULT_CHUNKSIZE;
    r->m_outChunkSize = RTMP_DEFAULT_CHUNKSIZE;
    r->m_bSendChunkSizeInfo = 1;
    r->m_nBufferMS = 30000;
    r->m_nClientBW = 2500000;
    r->m_nClientBW2 = 2;
    r->m_nServerBW = 2500000;
    r->m_fAudioCodecs = 3191.0;
    r->m_fVideoCodecs = 252.0;
    r->Link.curStreamIdx = 0;
    r->Link.nStreams = 0;
    r->Link.timeout = 30;
    r->Link.swfAge = 30;
}