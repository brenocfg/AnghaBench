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
struct TYPE_4__ {int cbSize; int cbWndExtra; void* hIconSm; int /*<<< orphan*/  lpszClassName; void* hbrBackground; void* hCursor; void* hIcon; void* hInstance; int /*<<< orphan*/  lpfnWndProc; } ;
typedef  TYPE_1__ WNDCLASSEXW ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/ * HMENU ;
typedef  void* HINSTANCE ;
typedef  void* HICON ;
typedef  void* HBRUSH ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  int /*<<< orphan*/  ATOM ;

/* Variables and functions */
 scalar_t__ COLOR_3DFACE ; 
 int /*<<< orphan*/  CW_USEDEFAULT ; 
 int /*<<< orphan*/  CheckMenuItem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ChildWndProc ; 
 scalar_t__ CreateStatusWindowW (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateWindowExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FrameWndProc ; 
 int /*<<< orphan*/ * GetSubMenu (void*,int) ; 
 int /*<<< orphan*/  GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_ARROW ; 
 int /*<<< orphan*/  IDI_REGEDIT ; 
 int /*<<< orphan*/  IDR_POPUP_MENUS ; 
 int /*<<< orphan*/  IDR_REGEDIT_MENU ; 
 int /*<<< orphan*/  ID_EDIT_MODIFY ; 
 int ID_EDIT_PERMISSIONS ; 
 int ID_VIEW_MENU ; 
 int /*<<< orphan*/  ID_VIEW_STATUSBAR ; 
 int /*<<< orphan*/  IMAGE_ICON ; 
 int /*<<< orphan*/  InitCommonControls () ; 
 int /*<<< orphan*/  InitializeAclUiDll () ; 
 int /*<<< orphan*/  LR_SHARED ; 
 void* LoadCursorW (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* LoadIconW (void*,int /*<<< orphan*/ ) ; 
 scalar_t__ LoadImageW (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* LoadMenuW (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LoadSettings () ; 
 int /*<<< orphan*/  MAKEINTRESOURCEW (int /*<<< orphan*/ ) ; 
 int MF_BYCOMMAND ; 
 int MF_BYPOSITION ; 
 int MF_CHECKED ; 
 int /*<<< orphan*/  RegisterClassExW (TYPE_1__*) ; 
 int /*<<< orphan*/  RegisterClipboardFormatW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegisterHexEditorClass (void*) ; 
 int /*<<< orphan*/  RemoveMenu (int /*<<< orphan*/ *,int,int) ; 
 int SBT_NOBORDERS ; 
 int /*<<< orphan*/  SM_CXSMICON ; 
 int /*<<< orphan*/  SM_CYSMICON ; 
 int /*<<< orphan*/  STATUS_WINDOW ; 
 int /*<<< orphan*/  SetMenuDefaultItem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SetupStatusBar (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ UlongToPtr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UpdateWindow (int /*<<< orphan*/ ) ; 
 int WS_CHILD ; 
 int WS_CLIPCHILDREN ; 
 int WS_CLIPSIBLINGS ; 
 int /*<<< orphan*/  WS_EX_WINDOWEDGE ; 
 int WS_OVERLAPPEDWINDOW ; 
 int WS_VISIBLE ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  hFrameWnd ; 
 void* hMenuFrame ; 
 void* hPopupMenus ; 
 scalar_t__ hStatusBar ; 
 int /*<<< orphan*/  nClipboardFormat ; 
 int /*<<< orphan*/  strClipboardFormat ; 
 int /*<<< orphan*/  szChildClass ; 
 int /*<<< orphan*/  szFrameClass ; 
 int /*<<< orphan*/  szTitle ; 

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    BOOL AclUiAvailable;
    HMENU hEditMenu;

    WNDCLASSEXW wcFrame;
    WNDCLASSEXW wcChild;
    ATOM hFrameWndClass;

    ZeroMemory(&wcFrame, sizeof(WNDCLASSEXW));
    wcFrame.cbSize = sizeof(WNDCLASSEXW);
    wcFrame.lpfnWndProc = FrameWndProc;
    wcFrame.hInstance = hInstance;
    wcFrame.hIcon = LoadIconW(hInstance, MAKEINTRESOURCEW(IDI_REGEDIT));
    wcFrame.hIconSm = (HICON)LoadImageW(hInstance, MAKEINTRESOURCEW(IDI_REGEDIT),
                                        IMAGE_ICON, GetSystemMetrics(SM_CXSMICON),
                                        GetSystemMetrics(SM_CYSMICON), LR_SHARED);
    wcFrame.hCursor = LoadCursorW(NULL, IDC_ARROW);
    wcFrame.hbrBackground = (HBRUSH)(COLOR_3DFACE + 1);
    wcFrame.lpszClassName = szFrameClass;

    hFrameWndClass = RegisterClassExW(&wcFrame); /* register frame window class */

    ZeroMemory(&wcChild, sizeof(WNDCLASSEXW));
    wcChild.cbSize = sizeof(WNDCLASSEXW);
    wcChild.lpfnWndProc = ChildWndProc;
    wcChild.cbWndExtra = sizeof(HANDLE);
    wcChild.hInstance = hInstance;
    wcChild.hIcon = LoadIconW(hInstance, MAKEINTRESOURCEW(IDI_REGEDIT));
    wcChild.hCursor = LoadCursorW(NULL, IDC_ARROW);
    wcChild.hbrBackground = (HBRUSH)(COLOR_3DFACE + 1);
    wcChild.lpszClassName = szChildClass;
    wcChild.hIconSm = (HICON)LoadImageW(hInstance, MAKEINTRESOURCEW(IDI_REGEDIT),
                                        IMAGE_ICON, GetSystemMetrics(SM_CXSMICON),
                                        GetSystemMetrics(SM_CYSMICON), LR_SHARED);

    RegisterClassExW(&wcChild); /* register child windows class */

    RegisterHexEditorClass(hInstance);

    hMenuFrame = LoadMenuW(hInstance, MAKEINTRESOURCEW(IDR_REGEDIT_MENU));
    hPopupMenus = LoadMenuW(hInstance, MAKEINTRESOURCEW(IDR_POPUP_MENUS));

    /* Initialize the Windows Common Controls DLL */
    // TODO: Replace this call by InitCommonControlsEx(_something_)
    InitCommonControls();

    hEditMenu = GetSubMenu(hMenuFrame, 1);

    AclUiAvailable = InitializeAclUiDll();
    if(!AclUiAvailable)
    {
        /* hide the Edit/Permissions... menu entry */
        if(hEditMenu != NULL)
        {
            RemoveMenu(hEditMenu, ID_EDIT_PERMISSIONS, MF_BYCOMMAND);
            /* remove the separator after the menu item */
            RemoveMenu(hEditMenu, 4, MF_BYPOSITION);
        }
    }

    if(hEditMenu != NULL)
        SetMenuDefaultItem(hEditMenu, ID_EDIT_MODIFY, MF_BYCOMMAND);

    nClipboardFormat = RegisterClipboardFormatW(strClipboardFormat);
    /* if (nClipboardFormat == 0) {
        DWORD dwError = GetLastError();
    } */

    hFrameWnd = CreateWindowExW(WS_EX_WINDOWEDGE, (LPCWSTR)(UlongToPtr(hFrameWndClass)), szTitle,
                                WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
                                CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                                NULL, hMenuFrame, hInstance, NULL/*lpParam*/);

    if (!hFrameWnd)
    {
        return FALSE;
    }

    /* Create the status bar */
    hStatusBar = CreateStatusWindowW(WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | SBT_NOBORDERS,
                                     L"", hFrameWnd, STATUS_WINDOW);
    if (hStatusBar)
    {
        /* Create the status bar panes */
        SetupStatusBar(hFrameWnd, FALSE);
        CheckMenuItem(GetSubMenu(hMenuFrame, ID_VIEW_MENU), ID_VIEW_STATUSBAR, MF_BYCOMMAND | MF_CHECKED);
    }

    LoadSettings();
    UpdateWindow(hFrameWnd);
    return TRUE;
}