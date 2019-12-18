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
struct TYPE_3__ {void* window; } ;
typedef  TYPE_1__ ole_clipbrd ;
typedef  void* HWND ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  IsWindow (void*) ; 
 int /*<<< orphan*/  S_OK ; 
 void* create_clipbrd_window () ; 

__attribute__((used)) static inline HRESULT get_clipbrd_window(ole_clipbrd *clipbrd, HWND *wnd)
{
#ifdef __REACTOS__
    /* The clipboard window can get destroyed if the  thread that created it dies so we may need to create it again */
    if (!IsWindow(clipbrd->window))
        clipbrd->window = create_clipbrd_window();
#endif

    if ( !clipbrd->window )
        clipbrd->window = create_clipbrd_window();

    *wnd = clipbrd->window;
    return *wnd ? S_OK : E_FAIL;
}