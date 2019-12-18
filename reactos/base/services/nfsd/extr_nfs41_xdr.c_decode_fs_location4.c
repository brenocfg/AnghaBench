#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct TYPE_8__ {char* address; } ;
typedef  TYPE_1__ fs_location_server ;
struct TYPE_9__ {int server_count; int /*<<< orphan*/  path; TYPE_1__* servers; } ;
typedef  TYPE_2__ fs_location4 ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int NFS41_HOSTNAME_LEN ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  decode_pathname4 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* realloc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  xdr_bytes (int /*<<< orphan*/ *,char**,int*,int) ; 
 int /*<<< orphan*/  xdr_u_int32_t (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static bool_t decode_fs_location4(
    XDR *xdr,
    fs_location4 *location)
{
    fs_location_server *arr;
    char *address;
    u_int32_t i, count, len;

    /* decode the number of servers */
    if (!xdr_u_int32_t(xdr, &count))
        return FALSE;

    /* allocate the fs_location_server array */
    if (count == 0) {
        free(location->servers);
        arr = NULL;
    } else if (count != location->server_count) {
        arr = realloc(location->servers, count * sizeof(fs_location_server));
        if (arr == NULL)
            return FALSE;
        ZeroMemory(arr, count * sizeof(fs_location_server));
    } else {
        arr = location->servers;
    }

    location->servers = arr;
    location->server_count = count;

    for (i = 0; i < count; i++) {
        len = NFS41_HOSTNAME_LEN;
        address = arr[i].address;
        if (!xdr_bytes(xdr, &address, &len, NFS41_HOSTNAME_LEN)) {
            free(arr);
            return FALSE;
        }
        arr[i].address[len] = '\0';
    }

    return decode_pathname4(xdr, &location->path);
}