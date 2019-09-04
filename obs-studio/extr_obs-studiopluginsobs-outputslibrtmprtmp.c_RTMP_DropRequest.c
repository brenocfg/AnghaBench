#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  m_numCalls; int /*<<< orphan*/  m_methodCalls; } ;
typedef  TYPE_1__ RTMP ;

/* Variables and functions */
 int /*<<< orphan*/  AV_erase (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 

void
RTMP_DropRequest(RTMP *r, int i, int freeit)
{
    AV_erase(r->m_methodCalls, &r->m_numCalls, i, freeit);
}