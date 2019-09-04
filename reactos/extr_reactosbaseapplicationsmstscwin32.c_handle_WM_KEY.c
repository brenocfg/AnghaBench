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
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int HIWORD (int /*<<< orphan*/ ) ; 
 int get_scan_code_from_ascii (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_key_down (int,int) ; 
 int /*<<< orphan*/  ui_key_up (int,int) ; 

__attribute__((used)) static LRESULT
handle_WM_KEY(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  int scancode;
  int ext;
  int down;

  ext = HIWORD(lParam);
  scancode = ext;
  down = !(ext & 0x8000);
  scancode &= 0xff;
  if (scancode == 0)
  {
    scancode = get_scan_code_from_ascii(wParam);
  }
  ext &= 0x0100;
  if (scancode == 0x0045) /* num lock */
  {
    ext &= ~0x0100;
  }
  if (down)
  {
    ui_key_down(scancode, ext);
  }
  else
  {
    ui_key_up(scancode, ext);
  }
  return 0;
}