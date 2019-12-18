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
struct RtfData {int dummy; } ;
typedef  int /*<<< orphan*/  HLPFILE ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HLPFILE_FindSubFile (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  HLPFILE_RtfAddGfxByAddr (struct RtfData*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  WINE_TRACE (char*,unsigned int) ; 
 int /*<<< orphan*/  WINE_WARN (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 

__attribute__((used)) static  BOOL    HLPFILE_RtfAddGfxByIndex(struct RtfData* rd, HLPFILE *hlpfile,
                                         unsigned index)
{
    char        tmp[16];
    BYTE        *ref, *end;

    WINE_TRACE("Loading picture #%d\n", index);

    sprintf(tmp, "|bm%u", index);

    if (!HLPFILE_FindSubFile(hlpfile, tmp, &ref, &end)) {WINE_WARN("no sub file\n"); return FALSE;}

    ref += 9;
    return HLPFILE_RtfAddGfxByAddr(rd, hlpfile, ref, end - ref);
}