#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_9__ {int version; int* TOMap; TYPE_1__* last_page; TYPE_1__* first_page; scalar_t__ hasPhrases40; scalar_t__ hasPhrases; } ;
struct TYPE_8__ {char* lpszMacro; struct TYPE_8__* next; } ;
struct TYPE_7__ {char* lpszTitle; unsigned int offset; unsigned int reference; int browse_bwd; int browse_fwd; TYPE_2__* first_macro; void* wNumber; int /*<<< orphan*/ * first_link; struct TYPE_7__* next; TYPE_3__* file; struct TYPE_7__* prev; } ;
typedef  TYPE_1__ HLPFILE_PAGE ;
typedef  TYPE_2__ HLPFILE_MACRO ;
typedef  TYPE_3__ HLPFILE ;
typedef  char BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 void* GET_UINT (char const*,int) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HLPFILE_Uncompress2 (TYPE_3__*,char const*,char const*,char*,char*) ; 
 int /*<<< orphan*/  HLPFILE_Uncompress3 (TYPE_3__*,char*,char*,char const*,char const*) ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WINE_FIXME (char*) ; 
 int /*<<< orphan*/  WINE_TRACE (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  WINE_WARN (char*) ; 
 int /*<<< orphan*/  debugstr_a (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,unsigned int) ; 
 int strlen (char*) ; 

__attribute__((used)) static BOOL HLPFILE_AddPage(HLPFILE *hlpfile, const BYTE *buf, const BYTE *end, unsigned ref, unsigned offset)
{
    HLPFILE_PAGE* page;
    const BYTE*   title;
    UINT          titlesize, blocksize, datalen;
    char*         ptr;
    HLPFILE_MACRO*macro;

    blocksize = GET_UINT(buf, 0);
    datalen = GET_UINT(buf, 0x10);
    title = buf + datalen;
    if (title > end) {WINE_WARN("page2\n"); return FALSE;};

    titlesize = GET_UINT(buf, 4);
    page = HeapAlloc(GetProcessHeap(), 0, sizeof(HLPFILE_PAGE) + titlesize + 1);
    if (!page) return FALSE;
    page->lpszTitle = (char*)page + sizeof(HLPFILE_PAGE);

    if (titlesize > blocksize - datalen)
    {
        /* need to decompress */
        if (hlpfile->hasPhrases)
            HLPFILE_Uncompress2(hlpfile, title, end, (BYTE*)page->lpszTitle, (BYTE*)page->lpszTitle + titlesize);
        else if (hlpfile->hasPhrases40)
            HLPFILE_Uncompress3(hlpfile, page->lpszTitle, page->lpszTitle + titlesize, title, end);
        else
        {
            WINE_FIXME("Text size is too long, splitting\n");
            titlesize = blocksize - datalen;
            memcpy(page->lpszTitle, title, titlesize);
        }
    }
    else
        memcpy(page->lpszTitle, title, titlesize);

    page->lpszTitle[titlesize] = '\0';

    if (hlpfile->first_page)
    {
        hlpfile->last_page->next = page;
        page->prev = hlpfile->last_page;
        hlpfile->last_page = page;
    }
    else
    {
        hlpfile->first_page = page;
        hlpfile->last_page = page;
        page->prev = NULL;
    }

    page->file            = hlpfile;
    page->next            = NULL;
    page->first_macro     = NULL;
    page->first_link      = NULL;
    page->wNumber         = GET_UINT(buf, 0x21);
    page->offset          = offset;
    page->reference       = ref;

    page->browse_bwd = GET_UINT(buf, 0x19);
    page->browse_fwd = GET_UINT(buf, 0x1D);

    if (hlpfile->version <= 16)
    {
        if (page->browse_bwd == 0xFFFF || page->browse_bwd == 0xFFFFFFFF)
            page->browse_bwd = 0xFFFFFFFF;
        else
            page->browse_bwd = hlpfile->TOMap[page->browse_bwd];

        if (page->browse_fwd == 0xFFFF || page->browse_fwd == 0xFFFFFFFF)
            page->browse_fwd = 0xFFFFFFFF;
        else
            page->browse_fwd = hlpfile->TOMap[page->browse_fwd];
    }

    WINE_TRACE("Added page[%d]: title=%s %08x << %08x >> %08x\n",
               page->wNumber, debugstr_a(page->lpszTitle),
               page->browse_bwd, page->offset, page->browse_fwd);

    /* now load macros */
    ptr = page->lpszTitle + strlen(page->lpszTitle) + 1;
    while (ptr < page->lpszTitle + titlesize)
    {
        unsigned len = strlen(ptr);
        char*    macro_str;

        WINE_TRACE("macro: %s\n", debugstr_a(ptr));
        macro = HeapAlloc(GetProcessHeap(), 0, sizeof(HLPFILE_MACRO) + len + 1);
        macro->lpszMacro = macro_str = (char*)(macro + 1);
        memcpy(macro_str, ptr, len + 1);
        /* FIXME: shall we really link macro in reverse order ??
         * may produce strange results when played at page opening
         */
        macro->next = page->first_macro;
        page->first_macro = macro;
        ptr += len + 1;
    }

    return TRUE;
}