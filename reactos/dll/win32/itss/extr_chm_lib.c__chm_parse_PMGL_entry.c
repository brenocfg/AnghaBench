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
struct chmUnitInfo {int space; scalar_t__ length; scalar_t__ start; int /*<<< orphan*/  path; } ;
typedef  scalar_t__ UInt64 ;
typedef  int /*<<< orphan*/  UChar ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ CHM_MAX_PATHLEN ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _chm_parse_UTF8 (int /*<<< orphan*/ **,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ _chm_parse_cword (int /*<<< orphan*/ **) ; 

__attribute__((used)) static BOOL _chm_parse_PMGL_entry(UChar **pEntry, struct chmUnitInfo *ui)
{
    UInt64 strLen;

    /* parse str len */
    strLen = _chm_parse_cword(pEntry);
    if (strLen > CHM_MAX_PATHLEN)
        return FALSE;

    /* parse path */
    if (! _chm_parse_UTF8(pEntry, strLen, ui->path))
        return FALSE;

    /* parse info */
    ui->space  = (int)_chm_parse_cword(pEntry);
    ui->start  = _chm_parse_cword(pEntry);
    ui->length = _chm_parse_cword(pEntry);
    return TRUE;
}