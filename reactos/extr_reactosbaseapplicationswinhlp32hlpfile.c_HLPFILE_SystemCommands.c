#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {char* lpszTitle; int tbsize; int dsize; unsigned short version; unsigned short flags; int charset; char* lpszCopyright; int contents_start; int numWindows; TYPE_3__* windows; int /*<<< orphan*/  hIcon; TYPE_4__* first_macro; void* compressed; } ;
struct TYPE_13__ {char* lpszMacro; struct TYPE_13__* next; } ;
struct TYPE_11__ {int cx; int cy; } ;
struct TYPE_10__ {int x; int y; } ;
struct TYPE_12__ {char* type; char* name; char* caption; int style; int sr_color; int nsr_color; TYPE_2__ size; TYPE_1__ origin; int /*<<< orphan*/  win_style; } ;
typedef  char* LPSTR ;
typedef  TYPE_3__ HLPFILE_WINDOWINFO ;
typedef  TYPE_4__ HLPFILE_MACRO ;
typedef  TYPE_5__ HLPFILE ;
typedef  int BYTE ;
typedef  void* BOOL ;

/* Variables and functions */
 int CW_USEDEFAULT ; 
 int /*<<< orphan*/  CreateIconFromResourceEx (int*,int,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int DEFAULT_CHARSET ; 
 void* FALSE ; 
 int GET_UINT (int*,int) ; 
 int GET_USHORT (int*,int) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 int /*<<< orphan*/  HLPFILE_FindSubFile (TYPE_5__*,char*,int**,int**) ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* HeapReAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int SW_SHOW ; 
 void* TRUE ; 
 int /*<<< orphan*/  WINE_FIXME (char*) ; 
 int /*<<< orphan*/  WINE_TRACE (char*,int,...) ; 
 int /*<<< orphan*/  WINE_WARN (char*,...) ; 
 int /*<<< orphan*/  WS_OVERLAPPEDWINDOW ; 
 int debugstr_a (char*) ; 
 int /*<<< orphan*/  lstrcpynA (char*,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static BOOL HLPFILE_SystemCommands(HLPFILE* hlpfile)
{
    BYTE *buf, *ptr, *end;
    HLPFILE_MACRO *macro, **m;
    LPSTR p;
    unsigned short magic, minor, major, flags;

    hlpfile->lpszTitle = NULL;

    if (!HLPFILE_FindSubFile(hlpfile, "|SYSTEM", &buf, &end)) return FALSE;

    magic = GET_USHORT(buf + 9, 0);
    minor = GET_USHORT(buf + 9, 2);
    major = GET_USHORT(buf + 9, 4);
    /* gen date on 4 bytes */
    flags = GET_USHORT(buf + 9, 10);
    WINE_TRACE("Got system header: magic=%04x version=%d.%d flags=%04x\n",
               magic, major, minor, flags);
    if (magic != 0x036C || major != 1)
    {WINE_WARN("Wrong system header\n"); return FALSE;}
    if (minor <= 16)
    {
        hlpfile->tbsize = 0x800;
        hlpfile->compressed = FALSE;
    }
    else if (flags == 0)
    {
        hlpfile->tbsize = 0x1000;
        hlpfile->compressed = FALSE;
    }
    else if (flags == 4)
    {
        hlpfile->tbsize = 0x1000;
        hlpfile->compressed = TRUE;
    }
    else
    {
        hlpfile->tbsize = 0x800;
        hlpfile->compressed = TRUE;
    }

    if (hlpfile->compressed)
        hlpfile->dsize = 0x4000;
    else
        hlpfile->dsize = hlpfile->tbsize - 0x0C;

    hlpfile->version = minor;
    hlpfile->flags = flags;
    hlpfile->charset = DEFAULT_CHARSET;

    if (hlpfile->version <= 16)
    {
        char *str = (char*)buf + 0x15;

        hlpfile->lpszTitle = HeapAlloc(GetProcessHeap(), 0, strlen(str) + 1);
        if (!hlpfile->lpszTitle) return FALSE;
        strcpy(hlpfile->lpszTitle, str);
        WINE_TRACE("Title: %s\n", debugstr_a(hlpfile->lpszTitle));
        /* Nothing more to parse */
        return TRUE;
    }
    for (ptr = buf + 0x15; ptr + 4 <= end; ptr += GET_USHORT(ptr, 2) + 4)
    {
        char *str = (char*) ptr + 4;
        switch (GET_USHORT(ptr, 0))
	{
	case 1:
            if (hlpfile->lpszTitle) {WINE_WARN("title\n"); break;}
            hlpfile->lpszTitle = HeapAlloc(GetProcessHeap(), 0, strlen(str) + 1);
            if (!hlpfile->lpszTitle) return FALSE;
            strcpy(hlpfile->lpszTitle, str);
            WINE_TRACE("Title: %s\n", debugstr_a(hlpfile->lpszTitle));
            break;

	case 2:
            if (hlpfile->lpszCopyright) {WINE_WARN("copyright\n"); break;}
            hlpfile->lpszCopyright = HeapAlloc(GetProcessHeap(), 0, strlen(str) + 1);
            if (!hlpfile->lpszCopyright) return FALSE;
            strcpy(hlpfile->lpszCopyright, str);
            WINE_TRACE("Copyright: %s\n", debugstr_a(hlpfile->lpszCopyright));
            break;

	case 3:
            if (GET_USHORT(ptr, 2) != 4) {WINE_WARN("system3\n");break;}
            hlpfile->contents_start = GET_UINT(ptr, 4);
            WINE_TRACE("Setting contents start at %08lx\n", hlpfile->contents_start);
            break;

	case 4:
            macro = HeapAlloc(GetProcessHeap(), 0, sizeof(HLPFILE_MACRO) + strlen(str) + 1);
            if (!macro) break;
            p = (char*)macro + sizeof(HLPFILE_MACRO);
            strcpy(p, str);
            macro->lpszMacro = p;
            macro->next = 0;
            for (m = &hlpfile->first_macro; *m; m = &(*m)->next);
            *m = macro;
            break;

        case 5:
            if (GET_USHORT(ptr, 4 + 4) != 1)
                WINE_FIXME("More than one icon, picking up first\n");
            /* 0x16 is sizeof(CURSORICONDIR), see user32/user_private.h */
            hlpfile->hIcon = CreateIconFromResourceEx(ptr + 4 + 0x16,
                                                      GET_USHORT(ptr, 2) - 0x16, TRUE,
                                                      0x30000, 0, 0, 0);
            break;

        case 6:
            if (GET_USHORT(ptr, 2) != 90) {WINE_WARN("system6\n");break;}

	    if (hlpfile->windows) 
        	hlpfile->windows = HeapReAlloc(GetProcessHeap(), 0, hlpfile->windows, 
                                           sizeof(HLPFILE_WINDOWINFO) * ++hlpfile->numWindows);
	    else 
        	hlpfile->windows = HeapAlloc(GetProcessHeap(), 0, 
                                           sizeof(HLPFILE_WINDOWINFO) * ++hlpfile->numWindows);
	    
            if (hlpfile->windows)
            {
                HLPFILE_WINDOWINFO* wi = &hlpfile->windows[hlpfile->numWindows - 1];

                flags = GET_USHORT(ptr, 4);
                if (flags & 0x0001) strcpy(wi->type, &str[2]);
                else wi->type[0] = '\0';
                if (flags & 0x0002) strcpy(wi->name, &str[12]);
                else wi->name[0] = '\0';
                if (flags & 0x0004) strcpy(wi->caption, &str[21]);
                else lstrcpynA(wi->caption, hlpfile->lpszTitle, sizeof(wi->caption));
                wi->origin.x = (flags & 0x0008) ? GET_USHORT(ptr, 76) : CW_USEDEFAULT;
                wi->origin.y = (flags & 0x0010) ? GET_USHORT(ptr, 78) : CW_USEDEFAULT;
                wi->size.cx = (flags & 0x0020) ? GET_USHORT(ptr, 80) : CW_USEDEFAULT;
                wi->size.cy = (flags & 0x0040) ? GET_USHORT(ptr, 82) : CW_USEDEFAULT;
                wi->style = (flags & 0x0080) ? GET_USHORT(ptr, 84) : SW_SHOW;
                wi->win_style = WS_OVERLAPPEDWINDOW;
                wi->sr_color = (flags & 0x0100) ? GET_UINT(ptr, 86) : 0xFFFFFF;
                wi->nsr_color = (flags & 0x0200) ? GET_UINT(ptr, 90) : 0xFFFFFF;
                WINE_TRACE("System-Window: flags=%c%c%c%c%c%c%c%c type=%s name=%s caption=%s (%d,%d)x(%d,%d)\n",
                           flags & 0x0001 ? 'T' : 't',
                           flags & 0x0002 ? 'N' : 'n',
                           flags & 0x0004 ? 'C' : 'c',
                           flags & 0x0008 ? 'X' : 'x',
                           flags & 0x0010 ? 'Y' : 'y',
                           flags & 0x0020 ? 'W' : 'w',
                           flags & 0x0040 ? 'H' : 'h',
                           flags & 0x0080 ? 'S' : 's',
                           debugstr_a(wi->type), debugstr_a(wi->name), debugstr_a(wi->caption), wi->origin.x, wi->origin.y,
                           wi->size.cx, wi->size.cy);
            }
            break;
        case 8:
            WINE_WARN("Citation: %s\n", debugstr_a((char *)ptr + 4));
            break;
        case 11:
            hlpfile->charset = ptr[4];
            WINE_TRACE("Charset: %d\n", hlpfile->charset);
            break;
	default:
            WINE_WARN("Unsupported SystemRecord[%d]\n", GET_USHORT(ptr, 0));
	}
    }
    if (!hlpfile->lpszTitle)
        hlpfile->lpszTitle = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, 1);
    return TRUE;
}