#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ WPARAM ;
struct TYPE_23__ {scalar_t__ ThemeActive; TYPE_3__* Theme; TYPE_1__* Color; int /*<<< orphan*/  Size; } ;
struct TYPE_22__ {scalar_t__ pwszFile; scalar_t__ pwszAction; } ;
struct TYPE_21__ {void* bInitializing; TYPE_9__ ActiveTheme; TYPE_3__* pThemes; int /*<<< orphan*/  hbmpThemePreview; int /*<<< orphan*/  hdcThemePreview; TYPE_9__ ClassicTheme; void* bSchemeChanged; void* bThemeChanged; int /*<<< orphan*/  Scheme; } ;
struct TYPE_20__ {scalar_t__ DisplayName; struct TYPE_20__* NextTheme; TYPE_1__* ColoursList; } ;
struct TYPE_19__ {int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; } ;
struct TYPE_18__ {int /*<<< orphan*/  ChildStyle; } ;
typedef  TYPE_2__ RECT ;
typedef  TYPE_3__* PTHEME ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  LONG_PTR ;
typedef  scalar_t__ INT_PTR ;
typedef  scalar_t__ INT ;
typedef  scalar_t__ HWND ;
typedef  int /*<<< orphan*/  HDC ;
typedef  TYPE_4__ GLOBALS ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AppearancePage_LoadSelectedScheme (scalar_t__,TYPE_4__*) ; 
 int /*<<< orphan*/  AppearancePage_ShowColorSchemes (scalar_t__,TYPE_4__*) ; 
 int /*<<< orphan*/  AppearancePage_ShowSizes (scalar_t__,TYPE_4__*) ; 
 int /*<<< orphan*/  AppearancePage_UpdateThemePreview (scalar_t__,TYPE_4__*) ; 
 int /*<<< orphan*/  CB_ADDSTRING ; 
 int /*<<< orphan*/  CB_SETCURSEL ; 
 int /*<<< orphan*/  CB_SETITEMDATA ; 
 int /*<<< orphan*/  CreateCompatibleBitmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWLP_USER ; 
 scalar_t__ FALSE ; 
 scalar_t__ FindOrAppendTheme (TYPE_3__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_9__*) ; 
 int /*<<< orphan*/  GetActiveClassicTheme (TYPE_3__*,TYPE_9__*) ; 
 int /*<<< orphan*/  GetActiveTheme (TYPE_3__*,TYPE_9__*) ; 
 int /*<<< orphan*/  GetClientRect (scalar_t__,TYPE_2__*) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ *) ; 
 scalar_t__ GetDlgItem (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetParent (scalar_t__) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 scalar_t__ HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IDC_APPEARANCE_PREVIEW ; 
 int /*<<< orphan*/  IDC_APPEARANCE_VISUAL_STYLE ; 
 int /*<<< orphan*/  LoadCurrentScheme (int /*<<< orphan*/ *) ; 
 TYPE_3__* LoadThemes () ; 
 int /*<<< orphan*/  PSM_CHANGED ; 
 int /*<<< orphan*/  PostMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SendMessage (scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowLongPtr (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* TRUE ; 
 TYPE_5__ g_GlobalData ; 
 scalar_t__ wcscmp (scalar_t__,char*) ; 

__attribute__((used)) static INT_PTR
AppearancePage_OnInit(HWND hwndDlg)
{
    INT iListIndex;
    HWND hwndTheme;
    GLOBALS *g;
    RECT rcPreview;
    HDC hdcScreen;
    PTHEME pTheme;

    g = (GLOBALS*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(GLOBALS));
    if (g == NULL)
        return FALSE;

    SetWindowLongPtr(hwndDlg, DWLP_USER, (LONG_PTR)g);

    g->bInitializing = TRUE;

    if (!LoadCurrentScheme(&g->Scheme))
        return FALSE;

    g->pThemes = LoadThemes();
    if (g->pThemes)
    {
        BOOL bLoadedTheme = FALSE;

        if (g_GlobalData.pwszAction && 
            g_GlobalData.pwszFile && 
            wcscmp(g_GlobalData.pwszAction, L"OpenMSTheme") == 0)
        {
            bLoadedTheme = FindOrAppendTheme(g->pThemes, 
                                             g_GlobalData.pwszFile,
                                             NULL,
                                             NULL,
                                             &g->ActiveTheme);
        }

        if (bLoadedTheme)
        {
            g->bThemeChanged = TRUE;
            g->bSchemeChanged = TRUE;

            PostMessageW(GetParent(hwndDlg), PSM_CHANGED, (WPARAM)hwndDlg, 0);

            AppearancePage_LoadSelectedScheme(hwndDlg, g);
        }
        else
        {
            if (!GetActiveTheme(g->pThemes, &g->ActiveTheme))
            {
                g->ActiveTheme.ThemeActive = FALSE;
            }
        }

        /*
         * Keep a copy of the selected classic theme in order to select this
         * when user selects the classic theme (and not a horrible random theme )
         */
        if (!GetActiveClassicTheme(g->pThemes, &g->ClassicTheme))
        {
            g->ClassicTheme.Theme = g->pThemes;
            g->ClassicTheme.Color = g->pThemes->ColoursList;
            g->ClassicTheme.Size = g->ClassicTheme.Color->ChildStyle;
        }

        if (g->ActiveTheme.ThemeActive == FALSE)
            g->ActiveTheme = g->ClassicTheme;

        GetClientRect(GetDlgItem(hwndDlg, IDC_APPEARANCE_PREVIEW), &rcPreview);

        hdcScreen = GetDC(NULL);
        g->hbmpThemePreview = CreateCompatibleBitmap(hdcScreen, rcPreview.right, rcPreview.bottom);
        g->hdcThemePreview = CreateCompatibleDC(hdcScreen);
        SelectObject(g->hdcThemePreview, g->hbmpThemePreview);
        ReleaseDC(NULL, hdcScreen);

        hwndTheme = GetDlgItem(hwndDlg, IDC_APPEARANCE_VISUAL_STYLE);

        for (pTheme = g->pThemes; pTheme; pTheme = pTheme->NextTheme)
        {
            iListIndex = SendMessage(hwndTheme, CB_ADDSTRING, 0, (LPARAM)pTheme->DisplayName);
            SendMessage(hwndTheme, CB_SETITEMDATA, iListIndex, (LPARAM)pTheme);
            if (pTheme == g->ActiveTheme.Theme)
            {
                SendMessage(hwndTheme, CB_SETCURSEL, (WPARAM)iListIndex, 0);
            }
        }

        if (g->ActiveTheme.Theme)
        {
            AppearancePage_ShowColorSchemes(hwndDlg, g);
            AppearancePage_ShowSizes(hwndDlg, g);
            AppearancePage_UpdateThemePreview(hwndDlg, g);
        }
    }
    g->bInitializing = FALSE;

    return FALSE;
}