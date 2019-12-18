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
struct tagMSIVIEW {int dummy; } ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  MSISTREAMSVIEW ;
typedef  int /*<<< orphan*/  MSIRECORD ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ STREAMS_insert_row (struct tagMSIVIEW*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ streams_find_row (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ streams_modify_update (struct tagMSIVIEW*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static UINT streams_modify_assign(struct tagMSIVIEW *view, MSIRECORD *rec)
{
    MSISTREAMSVIEW *sv = (MSISTREAMSVIEW *)view;
    UINT r;

    r = streams_find_row( sv, rec, NULL );
    if (r == ERROR_SUCCESS)
        return streams_modify_update(view, rec);

    return STREAMS_insert_row(view, rec, -1, FALSE);
}