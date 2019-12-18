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
struct TYPE_3__ {unsigned short len; scalar_t__ path; } ;
typedef  TYPE_1__ nfs41_abs_path ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int NFS41_MAX_PATH_LEN ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  xdr_bytes (int /*<<< orphan*/ *,char**,int*,int) ; 
 int /*<<< orphan*/  xdr_u_int32_t (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static bool_t decode_pathname4(
    XDR *xdr,
    nfs41_abs_path *path)
{
    char *pos;
    u_int32_t i, count, len, remaining;

    /* decode the number of components */
    if (!xdr_u_int32_t(xdr, &count))
        return FALSE;

    pos = (char *)path->path;
    remaining = NFS41_MAX_PATH_LEN;

    /* decode each component */
    for (i = 0; i < count; i++) {
        len = remaining;
        if (!xdr_bytes(xdr, (char **)&pos, &len, NFS41_MAX_PATH_LEN))
            return FALSE;
        remaining -= len;
        pos += len;

        if (i < count-1) { /* add a \ between components */
            if (remaining < 1)
                return FALSE;
            *pos++ = '\\';
            remaining--;
        }
    }
    path->len = (unsigned short)(NFS41_MAX_PATH_LEN - remaining);
    return TRUE;
}