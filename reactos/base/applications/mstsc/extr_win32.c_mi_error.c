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
typedef  int /*<<< orphan*/  TCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  MB_OK ; 
 int /*<<< orphan*/  MessageBox (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_Wnd ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  str_to_uni (int /*<<< orphan*/ *,char*) ; 

void
mi_error(char * msg)
{
#ifdef WITH_DEBUG
  printf(msg);
#else /* WITH_DEBUG */
  TCHAR lmsg[512];
  TCHAR ltitle[512];

  str_to_uni(lmsg, msg);
  str_to_uni(ltitle, "Error");
  MessageBox(g_Wnd, lmsg, ltitle, MB_OK);
#endif /* WITH_DEBUG */
}