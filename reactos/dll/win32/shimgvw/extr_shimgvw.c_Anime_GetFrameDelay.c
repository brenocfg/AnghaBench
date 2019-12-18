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
typedef  scalar_t__ UINT ;
struct TYPE_2__ {scalar_t__ value; } ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ m_nFrameCount ; 
 size_t m_nFrameIndex ; 
 TYPE_1__* m_pDelayItem ; 

DWORD Anime_GetFrameDelay(UINT nFrameIndex)
{
    if (nFrameIndex < m_nFrameCount && m_pDelayItem)
    {
        return ((DWORD *)m_pDelayItem->value)[m_nFrameIndex] * 10;
    }
    return 0;
}