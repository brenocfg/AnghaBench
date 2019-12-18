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
struct debug_buffer {int /*<<< orphan*/  str; } ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  LOCATION_TO_STR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WINED3D_LOCATION_BUFFER ; 
 int /*<<< orphan*/  WINED3D_LOCATION_DISCARDED ; 
 int /*<<< orphan*/  WINED3D_LOCATION_DRAWABLE ; 
 int /*<<< orphan*/  WINED3D_LOCATION_RB_MULTISAMPLE ; 
 int /*<<< orphan*/  WINED3D_LOCATION_RB_RESOLVED ; 
 int /*<<< orphan*/  WINED3D_LOCATION_SYSMEM ; 
 int /*<<< orphan*/  WINED3D_LOCATION_TEXTURE_RGB ; 
 int /*<<< orphan*/  WINED3D_LOCATION_TEXTURE_SRGB ; 
 int /*<<< orphan*/  WINED3D_LOCATION_USER_MEMORY ; 
 int /*<<< orphan*/  init_debug_buffer (struct debug_buffer*,char*) ; 
 char const* wine_dbg_sprintf (char*,char const*,int /*<<< orphan*/ ,char const*) ; 
 int wined3d_popcount (int) ; 

const char *wined3d_debug_location(DWORD location)
{
    struct debug_buffer buffer;
    const char *prefix = "";
    const char *suffix = "";

    if (wined3d_popcount(location) > 16)
    {
        prefix = "~(";
        location = ~location;
        suffix = ")";
    }

    init_debug_buffer(&buffer, "0");
#define LOCATION_TO_STR(x) if (location & x) { debug_append(&buffer, #x, " | "); location &= ~x; }
    LOCATION_TO_STR(WINED3D_LOCATION_DISCARDED);
    LOCATION_TO_STR(WINED3D_LOCATION_SYSMEM);
    LOCATION_TO_STR(WINED3D_LOCATION_USER_MEMORY);
    LOCATION_TO_STR(WINED3D_LOCATION_BUFFER);
    LOCATION_TO_STR(WINED3D_LOCATION_TEXTURE_RGB);
    LOCATION_TO_STR(WINED3D_LOCATION_TEXTURE_SRGB);
    LOCATION_TO_STR(WINED3D_LOCATION_DRAWABLE);
    LOCATION_TO_STR(WINED3D_LOCATION_RB_MULTISAMPLE);
    LOCATION_TO_STR(WINED3D_LOCATION_RB_RESOLVED);
#undef LOCATION_TO_STR
    if (location)
        FIXME("Unrecognized location flag(s) %#x.\n", location);

    return wine_dbg_sprintf("%s%s%s", prefix, buffer.str, suffix);
}