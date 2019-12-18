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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  GUID ;

/* Variables and functions */
 int /*<<< orphan*/  FrameDimensionPage ; 
 int /*<<< orphan*/  FrameDimensionTime ; 
 scalar_t__ GdipImageSelectActiveFrame (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ Ok ; 
 int /*<<< orphan*/  image ; 
 scalar_t__ m_nFrameCount ; 
 scalar_t__ m_nFrameIndex ; 

__attribute__((used)) static void Anime_SetFrameIndex(UINT nFrameIndex)
{
    if (nFrameIndex < m_nFrameCount)
    {
        GUID guid = FrameDimensionTime;
        if (Ok != GdipImageSelectActiveFrame(image, &guid, nFrameIndex))
        {
            guid = FrameDimensionPage;
            GdipImageSelectActiveFrame(image, &guid, nFrameIndex);
        }
    }
    m_nFrameIndex = nFrameIndex;
}