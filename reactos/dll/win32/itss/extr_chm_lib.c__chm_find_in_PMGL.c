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
struct chmPmglHeader {int /*<<< orphan*/ * free_space; } ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  UInt64 ;
typedef  int UInt32 ;
typedef  int /*<<< orphan*/  UChar ;

/* Variables and functions */
 int /*<<< orphan*/  CHM_MAX_PATHLEN ; 
 int _CHM_PMGL_LEN ; 
 int /*<<< orphan*/  _chm_parse_UTF8 (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _chm_parse_cword (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  _chm_skip_PMGL_entry_data (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  _unmarshal_pmgl_header (int /*<<< orphan*/ **,int*,struct chmPmglHeader*) ; 
 int /*<<< orphan*/  wcsicmp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static UChar *_chm_find_in_PMGL(UChar *page_buf,
                         UInt32 block_len,
                         const WCHAR *objPath)
{
    /* XXX: modify this to do a binary search using the nice index structure
     *      that is provided for us.
     */
    struct chmPmglHeader header;
    UInt32 hremain;
    UChar *end;
    UChar *cur;
    UChar *temp;
    UInt64 strLen;
    WCHAR buffer[CHM_MAX_PATHLEN+1];

    /* figure out where to start and end */
    cur = page_buf;
    hremain = _CHM_PMGL_LEN;
    if (! _unmarshal_pmgl_header(&cur, &hremain, &header))
        return NULL;
    end = page_buf + block_len - (header.free_space);

    /* now, scan progressively */
    while (cur < end)
    {
        /* grab the name */
        temp = cur;
        strLen = _chm_parse_cword(&cur);
        if (! _chm_parse_UTF8(&cur, strLen, buffer))
            return NULL;

        /* check if it is the right name */
        if (! wcsicmp(buffer, objPath))
            return temp;

        _chm_skip_PMGL_entry_data(&cur);
    }

    return NULL;
}