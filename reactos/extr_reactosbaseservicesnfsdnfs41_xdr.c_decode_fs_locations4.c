#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct TYPE_3__ {int location_count; int /*<<< orphan*/ * locations; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ fs_locations4 ;
typedef  int /*<<< orphan*/  fs_location4 ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ZeroMemory (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  decode_fs_location4 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decode_pathname4 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xdr_u_int32_t (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static bool_t decode_fs_locations4(
    XDR *xdr,
    fs_locations4 *locations)
{
    u_int32_t i, count;
    fs_location4 *arr;

    if (!decode_pathname4(xdr, &locations->path))
        return FALSE;

    if (!xdr_u_int32_t(xdr, &count))
        return FALSE;

    /* allocate the fs_location array */
    if (count == 0) {
        free(locations->locations);
        arr = NULL;
    } else if (count != locations->location_count) {
        arr = realloc(locations->locations, count * sizeof(fs_location4));
        if (arr == NULL)
            return FALSE;
        ZeroMemory(arr, count * sizeof(fs_location4));
    } else {
        arr = locations->locations;
    }

    locations->locations = arr;
    locations->location_count = count;

    for (i = 0; i < count; i++) {
        if (!decode_fs_location4(xdr, &arr[i])) {
            free(arr);
            return FALSE;
        }
    }
    return TRUE;
}