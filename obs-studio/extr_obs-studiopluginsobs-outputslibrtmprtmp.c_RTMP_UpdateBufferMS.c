#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  m_nBufferMS; int /*<<< orphan*/  m_stream_id; } ;
typedef  TYPE_1__ RTMP ;

/* Variables and functions */
 int /*<<< orphan*/  RTMP_SendCtrl (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
RTMP_UpdateBufferMS(RTMP *r)
{
    RTMP_SendCtrl(r, 3, r->m_stream_id, r->m_nBufferMS);
}