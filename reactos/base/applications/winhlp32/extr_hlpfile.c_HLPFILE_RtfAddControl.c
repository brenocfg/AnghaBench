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
struct RtfData {int /*<<< orphan*/  in_text; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HLPFILE_RtfAddRawString (struct RtfData*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WINE_TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_a (char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static BOOL HLPFILE_RtfAddControl(struct RtfData* rd, const char* str)
{
    WINE_TRACE("%s\n", debugstr_a(str));
    if (*str == '\\' || *str == '{') rd->in_text = FALSE;
    else if (*str == '}') rd->in_text = TRUE;
    return HLPFILE_RtfAddRawString(rd, str, strlen(str));
}