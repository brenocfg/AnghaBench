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
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,scalar_t__) ; 
 int /*<<< orphan*/  WINED3DUSAGEQUERY_TO_STR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WINED3DUSAGE_QUERY_FILTER ; 
 int /*<<< orphan*/  WINED3DUSAGE_QUERY_GENMIPMAP ; 
 int /*<<< orphan*/  WINED3DUSAGE_QUERY_LEGACYBUMPMAP ; 
 int /*<<< orphan*/  WINED3DUSAGE_QUERY_POSTPIXELSHADER_BLENDING ; 
 int /*<<< orphan*/  WINED3DUSAGE_QUERY_SRGBREAD ; 
 int /*<<< orphan*/  WINED3DUSAGE_QUERY_SRGBWRITE ; 
 int /*<<< orphan*/  WINED3DUSAGE_QUERY_VERTEXTEXTURE ; 
 int /*<<< orphan*/  WINED3DUSAGE_QUERY_WRAPANDMIP ; 
 int /*<<< orphan*/  init_debug_buffer (struct debug_buffer*,char*) ; 
 char const* wine_dbg_sprintf (char*,int /*<<< orphan*/ ) ; 

const char *debug_d3dusagequery(DWORD usage)
{
    struct debug_buffer buffer;

    init_debug_buffer(&buffer, "0");
#define WINED3DUSAGEQUERY_TO_STR(x) if (usage & x) { debug_append(&buffer, #x, " | "); usage &= ~x; }
    WINED3DUSAGEQUERY_TO_STR(WINED3DUSAGE_QUERY_FILTER);
    WINED3DUSAGEQUERY_TO_STR(WINED3DUSAGE_QUERY_GENMIPMAP);
    WINED3DUSAGEQUERY_TO_STR(WINED3DUSAGE_QUERY_LEGACYBUMPMAP);
    WINED3DUSAGEQUERY_TO_STR(WINED3DUSAGE_QUERY_POSTPIXELSHADER_BLENDING);
    WINED3DUSAGEQUERY_TO_STR(WINED3DUSAGE_QUERY_SRGBREAD);
    WINED3DUSAGEQUERY_TO_STR(WINED3DUSAGE_QUERY_SRGBWRITE);
    WINED3DUSAGEQUERY_TO_STR(WINED3DUSAGE_QUERY_VERTEXTEXTURE);
    WINED3DUSAGEQUERY_TO_STR(WINED3DUSAGE_QUERY_WRAPANDMIP);
#undef WINED3DUSAGEQUERY_TO_STR
    if (usage)
        FIXME("Unrecognized usage query flag(s) %#x.\n", usage);

    return wine_dbg_sprintf("%s", buffer.str);
}