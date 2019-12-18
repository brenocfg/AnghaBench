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
struct TYPE_3__ {unsigned char* data; int /*<<< orphan*/  data_len; int /*<<< orphan*/  eof; } ;
typedef  TYPE_1__ nfs41_read_res_ok ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NFS41_MAX_FILEIO_SIZE ; 
 int /*<<< orphan*/  xdr_bool (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_bytes (int /*<<< orphan*/ *,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool_t decode_read_res_ok(
    XDR *xdr,
    nfs41_read_res_ok *res)
{
    unsigned char *data = res->data;

    if (!xdr_bool(xdr, &res->eof))
        return FALSE;

    return xdr_bytes(xdr, (char **)&data, &res->data_len, NFS41_MAX_FILEIO_SIZE);
}