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
typedef  int (* HLPFILE_BPTreeCompare ) (void*,void const*,int,void**) ;
typedef  void BYTE ;

/* Variables and functions */
 int GET_SHORT (void*,int) ; 
 unsigned int GET_USHORT (void*,int) ; 
 int /*<<< orphan*/  WINE_ERR (char*,unsigned int) ; 

__attribute__((used)) static void* HLPFILE_BPTreeSearch(BYTE* buf, const void* key,
                           HLPFILE_BPTreeCompare comp)
{
    unsigned magic;
    unsigned page_size;
    unsigned cur_page;
    unsigned level;
    BYTE *pages, *ptr, *newptr;
    int i, entries;
    int ret;

    magic = GET_USHORT(buf, 9);
    if (magic != 0x293B)
    {
        WINE_ERR("Invalid magic in B+ tree: 0x%x\n", magic);
        return NULL;
    }
    page_size = GET_USHORT(buf, 9+4);
    cur_page  = GET_USHORT(buf, 9+26);
    level     = GET_USHORT(buf, 9+32);
    pages     = buf + 9 + 38;
    while (--level > 0)
    {
        ptr = pages + cur_page*page_size;
        entries = GET_SHORT(ptr, 2);
        ptr += 6;
        for (i = 0; i < entries; i++)
        {
            if (comp(ptr, key, 0, (void **)&newptr) > 0) break;
            ptr = newptr;
        }
        cur_page = GET_USHORT(ptr-2, 0);
    }
    ptr = pages + cur_page*page_size;
    entries = GET_SHORT(ptr, 2);
    ptr += 8;
    for (i = 0; i < entries; i++)
    {
        ret = comp(ptr, key, 1, (void **)&newptr);
        if (ret == 0) return ptr;
        if (ret > 0) return NULL;
        ptr = newptr;
    }
    return NULL;
}