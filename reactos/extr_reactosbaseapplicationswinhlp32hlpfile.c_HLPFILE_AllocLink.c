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
struct RtfData {TYPE_1__* current_link; int /*<<< orphan*/  char_pos; void* force_color; TYPE_1__* first_link; } ;
struct TYPE_4__ {int cookie; char* string; unsigned int window; int /*<<< orphan*/  hash; int /*<<< orphan*/  cpMax; int /*<<< orphan*/  cpMin; struct TYPE_4__* next; void* bHotSpot; void* bClrChange; } ;
typedef  int /*<<< orphan*/  LONG ;
typedef  TYPE_1__ HLPFILE_LINK ;
typedef  int /*<<< orphan*/  HLPFILE_HOTSPOTLINK ;
typedef  void* BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  WINE_FIXME (char*) ; 
 int /*<<< orphan*/  WINE_TRACE (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  debugstr_a (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,unsigned int) ; 
 unsigned int strlen (char const*) ; 

__attribute__((used)) static HLPFILE_LINK*       HLPFILE_AllocLink(struct RtfData* rd, int cookie,
                                             const char* str, unsigned len, LONG hash,
                                             BOOL clrChange, BOOL bHotSpot, unsigned wnd)
{
    HLPFILE_LINK*  link;
    char*          link_str;
    unsigned       asz = bHotSpot ? sizeof(HLPFILE_HOTSPOTLINK) : sizeof(HLPFILE_LINK);

    /* FIXME: should build a string table for the attributes.link.lpszPath
     * they are reallocated for each link
     */
    if (len == -1) len = strlen(str);
    link = HeapAlloc(GetProcessHeap(), 0, asz + len + 1);
    if (!link) return NULL;

    link->cookie     = cookie;
    link->string     = link_str = (char*)link + asz;
    memcpy(link_str, str, len);
    link_str[len] = '\0';
    link->hash       = hash;
    link->bClrChange = clrChange;
    link->bHotSpot   = bHotSpot;
    link->window     = wnd;
    link->next       = rd->first_link;
    rd->first_link   = link;
    link->cpMin      = rd->char_pos;
    rd->force_color  = clrChange;
    if (rd->current_link) WINE_FIXME("Pending link\n");
    if (bHotSpot)
        link->cpMax = rd->char_pos;
    else
        rd->current_link = link;

    WINE_TRACE("Link[%d] to %s@%08x:%d\n",
               link->cookie, debugstr_a(link->string), link->hash, link->window);
    return link;
}