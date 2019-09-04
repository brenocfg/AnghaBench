#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int cbSize; int /*<<< orphan*/ * hIconSm; int /*<<< orphan*/  lpszClassName; int /*<<< orphan*/ * lpszMenuName; int /*<<< orphan*/  hbrBackground; int /*<<< orphan*/  hCursor; int /*<<< orphan*/ * hIcon; int /*<<< orphan*/  hInstance; scalar_t__ cbWndExtra; scalar_t__ cbClsExtra; int /*<<< orphan*/  lpfnWndProc; int /*<<< orphan*/  style; } ;
typedef  TYPE_1__ WNDCLASSEXW ;
typedef  int /*<<< orphan*/  WNDCLASSEX ;
typedef  int /*<<< orphan*/  HINSTANCE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CS_DBLCLKS ; 
 int /*<<< orphan*/  DisplayProc ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetStockObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_ARROW ; 
 int /*<<< orphan*/  LoadCursor (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegisterClassExW (TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WHITE_BRUSH ; 
 int /*<<< orphan*/  g_szFontDisplayClassName ; 

BOOL
Display_InitClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wincl;

	/* Set the fontdisplay window class structure */
	wincl.cbSize = sizeof(WNDCLASSEX);
	wincl.style = CS_DBLCLKS;
	wincl.lpfnWndProc = DisplayProc;
	wincl.cbClsExtra = 0;
	wincl.cbWndExtra = 0;
	wincl.hInstance = hInstance;
	wincl.hIcon = NULL;
	wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
	wincl.hbrBackground = GetStockObject(WHITE_BRUSH);
	wincl.lpszMenuName = NULL;
	wincl.lpszClassName = g_szFontDisplayClassName;
	wincl.hIconSm = NULL;

	/* Register the window class, and if it fails return FALSE */
	if (!RegisterClassExW (&wincl))
	{
		return FALSE;
	}
	return TRUE;
}