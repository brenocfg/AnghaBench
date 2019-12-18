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
struct chmUnitInfo {int dummy; } ;
struct chmFile {int block_len; int index_root; scalar_t__ dir_offset; } ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int UInt64 ;
typedef  int /*<<< orphan*/  UChar ;
typedef  int Int32 ;

/* Variables and functions */
 int CHM_RESOLVE_FAILURE ; 
 int CHM_RESOLVE_SUCCESS ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int _chm_fetch_bytes (struct chmFile*,int /*<<< orphan*/ *,scalar_t__,int) ; 
 int _chm_find_in_PMGI (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * _chm_find_in_PMGL (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  _chm_parse_PMGL_entry (int /*<<< orphan*/ **,struct chmUnitInfo*) ; 
 int /*<<< orphan*/  _chm_pmgi_marker ; 
 int /*<<< orphan*/  _chm_pmgl_marker ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int chm_resolve_object(struct chmFile *h,
                       const WCHAR *objPath,
                       struct chmUnitInfo *ui)
{
    /*
     * XXX: implement caching scheme for dir pages
     */

    Int32 curPage;

    /* buffer to hold whatever page we're looking at */
    UChar *page_buf = HeapAlloc(GetProcessHeap(), 0, h->block_len);

    /* starting page */
    curPage = h->index_root;

    /* until we have either returned or given up */
    while (curPage != -1)
    {

        /* try to fetch the index page */
        if (_chm_fetch_bytes(h, page_buf,
                             h->dir_offset + (UInt64)curPage*h->block_len,
                             h->block_len) != h->block_len)
	{
	    HeapFree(GetProcessHeap(), 0, page_buf);
            return CHM_RESOLVE_FAILURE;
	}

        /* now, if it is a leaf node: */
        if (memcmp(page_buf, _chm_pmgl_marker, 4) == 0)
        {
            /* scan block */
            UChar *pEntry = _chm_find_in_PMGL(page_buf,
                                              h->block_len,
                                              objPath);
            if (pEntry == NULL)
            {
	        HeapFree(GetProcessHeap(), 0, page_buf);
                return CHM_RESOLVE_FAILURE;
            }

            /* parse entry and return */
            _chm_parse_PMGL_entry(&pEntry, ui);
	    HeapFree(GetProcessHeap(), 0, page_buf);
            return CHM_RESOLVE_SUCCESS;
        }

        /* else, if it is a branch node: */
        else if (memcmp(page_buf, _chm_pmgi_marker, 4) == 0)
            curPage = _chm_find_in_PMGI(page_buf, h->block_len, objPath);

        /* else, we are confused.  give up. */
        else
        {
	    HeapFree(GetProcessHeap(), 0, page_buf);
            return CHM_RESOLVE_FAILURE;
        }
    }

    /* didn't find anything.  fail. */
    HeapFree(GetProcessHeap(), 0, page_buf);
    return CHM_RESOLVE_FAILURE;
}