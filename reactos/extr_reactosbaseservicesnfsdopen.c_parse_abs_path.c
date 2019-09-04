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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int len; int* path; } ;
typedef  TYPE_1__ nfs41_abs_path ;
typedef  int /*<<< orphan*/  USHORT ;

/* Variables and functions */
 int ERROR_BUFFER_OVERFLOW ; 
 int NFS41_MAX_PATH_LEN ; 
 int safe_read (unsigned char**,int /*<<< orphan*/ *,int*,int) ; 

__attribute__((used)) static int parse_abs_path(unsigned char **buffer, uint32_t *length, nfs41_abs_path *path)
{
    int status = safe_read(buffer, length, &path->len, sizeof(USHORT));
    if (status) goto out;
    if (path->len == 0)
        goto out;
    if (path->len >= NFS41_MAX_PATH_LEN) {
        status = ERROR_BUFFER_OVERFLOW;
        goto out;
    }
    status = safe_read(buffer, length, path->path, path->len);
    if (status) goto out;
    path->len--; /* subtract 1 for null */
out:
    return status;
}