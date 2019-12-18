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
typedef  int /*<<< orphan*/  IUri ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IUri_IsEqual (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUri_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_uri_nofrag (int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL compare_ignoring_frag(IUri *uri1, IUri *uri2)
{
    IUri *uri_nofrag1, *uri_nofrag2;
    BOOL ret = FALSE;

    uri_nofrag1 = get_uri_nofrag(uri1);
    if(!uri_nofrag1)
        return FALSE;

    uri_nofrag2 = get_uri_nofrag(uri2);
    if(uri_nofrag2) {
        IUri_IsEqual(uri_nofrag1, uri_nofrag2, &ret);
        IUri_Release(uri_nofrag2);
    }

    IUri_Release(uri_nofrag1);
    return ret;
}