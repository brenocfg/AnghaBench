#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct RtfData {int dummy; } ;
typedef  scalar_t__ ULONG ;
struct TYPE_7__ {char const* lpszPath; TYPE_1__* windows; int /*<<< orphan*/  numWindows; } ;
struct TYPE_6__ {void* height; void* width; void* y; void* x; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ HLPFILE_HOTSPOTLINK ;
typedef  TYPE_3__ HLPFILE ;
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GET_UINT (int const*,int) ; 
 void* GET_USHORT (int const*,int) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__ HLPFILE_AllocLink (struct RtfData*,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HLPFILE_Hash (char const*) ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WINE_FIXME (char*,int const) ; 
 int /*<<< orphan*/  WINE_TRACE (char*,int const,int const,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WINE_WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_a (char const*) ; 
 int /*<<< orphan*/  hlp_link_link ; 
 int /*<<< orphan*/  hlp_link_macro ; 
 int /*<<< orphan*/  hlp_link_popup ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void HLPFILE_AddHotSpotLinks(struct RtfData* rd, HLPFILE* file,
                                    const BYTE* start, ULONG hs_size, ULONG hs_offset)
{
    unsigned    i, hs_num;
    ULONG       hs_macro;
    const char* str;

    if (hs_size == 0 || hs_offset == 0) return;

    start += hs_offset;
    /* always 1 ?? */
    hs_num = GET_USHORT(start, 1);
    hs_macro = GET_UINT(start, 3);

    str = (const char*)start + 7 + 15 * hs_num + hs_macro;
    /* FIXME: should use hs_size to prevent out of bounds reads */
    for (i = 0; i < hs_num; i++)
    {
        HLPFILE_HOTSPOTLINK*    hslink;

        WINE_TRACE("%02x-%02x%02x {%s,%s}\n",
                   start[7 + 15 * i + 0], start[7 + 15 * i + 1], start[7 + 15 * i + 2],
                   debugstr_a(str), debugstr_a(str + strlen(str) + 1));
        /* str points to two null terminated strings:
         * hotspot name, then link name
         */
        str += strlen(str) + 1;     /* skip hotspot name */

        hslink = NULL;
        switch (start[7 + 15 * i + 0])
        /* The next two chars always look like 0x04 0x00 ???
         * What are they for ?
         */
        {
        case 0xC8:
            hslink = (HLPFILE_HOTSPOTLINK*)
                HLPFILE_AllocLink(rd, hlp_link_macro, str, -1, 0, FALSE, TRUE, -1);
            break;

        case 0xE6:
        case 0xE7:
            hslink = (HLPFILE_HOTSPOTLINK*)
                HLPFILE_AllocLink(rd, (start[7 + 15 * i + 0] & 1) ? hlp_link_link : hlp_link_popup,
                                  file->lpszPath, -1, HLPFILE_Hash(str),
                                  FALSE, TRUE, -1);
            break;

        case 0xEE:
        case 0xEF:
            {
                const char* win = strchr(str, '>');
                int wnd = -1;
                char* tgt = NULL;

                if (win)
                {
                    for (wnd = file->numWindows - 1; wnd >= 0; wnd--)
                    {
                        if (!strcmp(win + 1, file->windows[wnd].name)) break;
                    }
                    if (wnd == -1)
                        WINE_WARN("Couldn't find window info for %s\n", debugstr_a(win));
                    if ((tgt = HeapAlloc(GetProcessHeap(), 0, win - str + 1)))
                    {
                        memcpy(tgt, str, win - str);
                        tgt[win - str] = '\0';
                    }
                }
                hslink = (HLPFILE_HOTSPOTLINK*)
                    HLPFILE_AllocLink(rd, (start[7 + 15 * i + 0] & 1) ? hlp_link_link : hlp_link_popup,
                                      file->lpszPath, -1, HLPFILE_Hash(tgt ? tgt : str), FALSE, TRUE, wnd);
                HeapFree(GetProcessHeap(), 0, tgt);
                break;
            }
        default:
            WINE_FIXME("unknown hotsport target 0x%x\n", start[7 + 15 * i + 0]);
        }
        if (hslink)
        {
            hslink->x      = GET_USHORT(start, 7 + 15 * i + 3);
            hslink->y      = GET_USHORT(start, 7 + 15 * i + 5);
            hslink->width  = GET_USHORT(start, 7 + 15 * i + 7);
            hslink->height = GET_USHORT(start, 7 + 15 * i + 9);
            /* target = GET_UINT(start, 7 + 15 * i + 11); */
        }
        str += strlen(str) + 1;
    }
}