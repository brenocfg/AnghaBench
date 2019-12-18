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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
#define  NFS_LIMIT_BLOCKS 129 
#define  NFS_LIMIT_SIZE 128 
 int /*<<< orphan*/  decode_modified_limit4 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eprintf (char*,int) ; 
 int /*<<< orphan*/  xdr_u_hyper (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_u_int32_t (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static bool_t decode_space_limit4(
    XDR *xdr,
    uint64_t *filesize)
{
    uint32_t limitby;

    if (!xdr_u_int32_t(xdr, &limitby))
        return FALSE;

    switch (limitby)
    {
    case NFS_LIMIT_SIZE:
        return xdr_u_hyper(xdr, filesize);
    case NFS_LIMIT_BLOCKS:
        return decode_modified_limit4(xdr, filesize);
    default:
        eprintf("decode_space_limit4: limitby %d invalid\n", limitby);
        return FALSE;
    }
}