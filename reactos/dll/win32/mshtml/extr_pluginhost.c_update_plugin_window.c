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
struct TYPE_4__ {scalar_t__ hwnd; int /*<<< orphan*/  rect; scalar_t__ ip_object; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  TYPE_1__ PluginHost ;
typedef  scalar_t__ HWND ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  IOleInPlaceObject_SetObjectRects (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  embed_plugin_object (TYPE_1__*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wine_dbgstr_rect (int /*<<< orphan*/  const*) ; 

void update_plugin_window(PluginHost *host, HWND hwnd, const RECT *rect)
{
    BOOL rect_changed = FALSE;

    if(!hwnd || (host->hwnd && host->hwnd != hwnd)) {
        FIXME("unhandled hwnd\n");
        return;
    }

    TRACE("%p %s\n", hwnd, wine_dbgstr_rect(rect));

    if(memcmp(rect, &host->rect, sizeof(RECT))) {
        host->rect = *rect;
        rect_changed = TRUE;
    }

    if(!host->hwnd) {
        host->hwnd = hwnd;
        embed_plugin_object(host);
    }

    if(rect_changed && host->ip_object)
        IOleInPlaceObject_SetObjectRects(host->ip_object, &host->rect, &host->rect);
}