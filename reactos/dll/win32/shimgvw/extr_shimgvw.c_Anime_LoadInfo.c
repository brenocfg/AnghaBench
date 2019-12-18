#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WORD ;
typedef  scalar_t__ UINT ;
struct TYPE_8__ {scalar_t__ value; } ;
typedef  TYPE_1__ PropertyItem ;
typedef  TYPE_1__ GUID ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ANIME_TIMER_ID ; 
 int /*<<< orphan*/  Anime_FreeInfo () ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GdipGetPropertyItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  GdipGetPropertyItemSize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  GdipImageGetFrameCount (int /*<<< orphan*/ ,TYPE_1__*,scalar_t__*) ; 
 int /*<<< orphan*/  GdipImageGetFrameDimensionsCount (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  GdipImageGetFrameDimensionsList (int /*<<< orphan*/ ,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  KillTimer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ Ok ; 
 int /*<<< orphan*/  PropertyTagFrameDelay ; 
 int /*<<< orphan*/  PropertyTagLoopCount ; 
 int /*<<< orphan*/  SetTimer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ calloc (scalar_t__,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  hDispWnd ; 
 int /*<<< orphan*/  image ; 
 scalar_t__ m_nFrameCount ; 
 int /*<<< orphan*/  m_nLoopCount ; 
 TYPE_1__* m_pDelayItem ; 
 scalar_t__ malloc (scalar_t__) ; 

__attribute__((used)) static BOOL Anime_LoadInfo(void)
{
    GUID *dims;
    UINT nDimCount = 0;
    UINT cbItem;
    UINT result;
    PropertyItem *pItem;

    Anime_FreeInfo();
    KillTimer(hDispWnd, ANIME_TIMER_ID);

    if (!image)
        return FALSE;

    GdipImageGetFrameDimensionsCount(image, &nDimCount);
    if (nDimCount)
    {
        dims = (GUID *)calloc(nDimCount, sizeof(GUID));
        if (dims)
        {
            GdipImageGetFrameDimensionsList(image, dims, nDimCount);
            GdipImageGetFrameCount(image, dims, &result);
            m_nFrameCount = result;
            free(dims);
        }
    }

    result = 0;
    GdipGetPropertyItemSize(image, PropertyTagFrameDelay, &result);
    cbItem = result;
    if (cbItem)
    {
        m_pDelayItem = (PropertyItem *)malloc(cbItem);
        GdipGetPropertyItem(image, PropertyTagFrameDelay, cbItem, m_pDelayItem);
    }

    result = 0;
    GdipGetPropertyItemSize(image, PropertyTagLoopCount, &result);
    cbItem = result;
    if (cbItem)
    {
        pItem = (PropertyItem *)malloc(cbItem);
        if (pItem)
        {
            if (GdipGetPropertyItem(image, PropertyTagLoopCount, cbItem, pItem) == Ok)
            {
                m_nLoopCount = *(WORD *)pItem->value;
            }
            free(pItem);
        }
    }

    if (m_pDelayItem)
    {
        SetTimer(hDispWnd, ANIME_TIMER_ID, 0, NULL);
    }

    return m_pDelayItem != NULL;
}