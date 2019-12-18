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
struct TYPE_4__ {unsigned int topic_maplen; unsigned int tbsize; int dsize; int /*<<< orphan*/ ** topic_map; int /*<<< orphan*/ * topic_end; scalar_t__ compressed; } ;
typedef  TYPE_1__ HLPFILE ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HLPFILE_FindSubFile (TYPE_1__*,char*,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * HLPFILE_UncompressLZ77 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ HLPFILE_UncompressedLZ77_Size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WINE_WARN (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL HLPFILE_Uncompress_Topic(HLPFILE* hlpfile)
{
    BYTE *buf, *ptr, *end, *newptr;
    unsigned int i, newsize = 0;
    unsigned int topic_size;

    if (!HLPFILE_FindSubFile(hlpfile, "|TOPIC", &buf, &end))
    {WINE_WARN("topic0\n"); return FALSE;}

    buf += 9; /* Skip file header */
    topic_size = end - buf;
    if (hlpfile->compressed)
    {
        hlpfile->topic_maplen = (topic_size - 1) / hlpfile->tbsize + 1;

        for (i = 0; i < hlpfile->topic_maplen; i++)
        {
            ptr = buf + i * hlpfile->tbsize;

            /* I don't know why, it's necessary for printman.hlp */
            if (ptr + 0x44 > end) ptr = end - 0x44;

            newsize += HLPFILE_UncompressedLZ77_Size(ptr + 0xc, min(end, ptr + hlpfile->tbsize));
        }

        hlpfile->topic_map = HeapAlloc(GetProcessHeap(), 0,
                                       hlpfile->topic_maplen * sizeof(hlpfile->topic_map[0]) + newsize);
        if (!hlpfile->topic_map) return FALSE;
        newptr = (BYTE*)(hlpfile->topic_map + hlpfile->topic_maplen);
        hlpfile->topic_end = newptr + newsize;

        for (i = 0; i < hlpfile->topic_maplen; i++)
        {
            ptr = buf + i * hlpfile->tbsize;
            if (ptr + 0x44 > end) ptr = end - 0x44;

            hlpfile->topic_map[i] = newptr;
            newptr = HLPFILE_UncompressLZ77(ptr + 0xc, min(end, ptr + hlpfile->tbsize), newptr);
        }
    }
    else
    {
        /* basically, we need to copy the TopicBlockSize byte pages
         * (removing the first 0x0C) in one single area in memory
         */
        hlpfile->topic_maplen = (topic_size - 1) / hlpfile->tbsize + 1;
        hlpfile->topic_map = HeapAlloc(GetProcessHeap(), 0,
                                       hlpfile->topic_maplen * (sizeof(hlpfile->topic_map[0]) + hlpfile->dsize));
        if (!hlpfile->topic_map) return FALSE;
        newptr = (BYTE*)(hlpfile->topic_map + hlpfile->topic_maplen);
        hlpfile->topic_end = newptr + topic_size;

        for (i = 0; i < hlpfile->topic_maplen; i++)
        {
            hlpfile->topic_map[i] = newptr + i * hlpfile->dsize;
            memcpy(hlpfile->topic_map[i], buf + i * hlpfile->tbsize + 0x0C, hlpfile->dsize);
        }
    }
    return TRUE;
}