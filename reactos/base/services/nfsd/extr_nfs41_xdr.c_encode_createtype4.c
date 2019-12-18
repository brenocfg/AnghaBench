#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int specdata1; int specdata2; } ;
struct TYPE_6__ {char* linkdata; int /*<<< orphan*/  linkdata_len; } ;
struct TYPE_8__ {TYPE_2__ devdata; TYPE_1__ lnk; } ;
struct TYPE_9__ {int type; TYPE_3__ u; } ;
typedef  TYPE_4__ createtype4 ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
#define  NF4BLK 130 
#define  NF4CHR 129 
#define  NF4LNK 128 
 int /*<<< orphan*/  NFS4_OPAQUE_LIMIT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  xdr_bytes (int /*<<< orphan*/ *,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_u_int32_t (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static bool_t encode_createtype4(
    XDR *xdr,
    createtype4 *ct)
{
    bool_t result = TRUE;
    const char *linkdata;

    if (!xdr_u_int32_t(xdr, &ct->type))
        return FALSE;

    switch (ct->type)
    {
    case NF4LNK:
        linkdata = ct->u.lnk.linkdata;
        result = xdr_bytes(xdr, (char**)&linkdata, &ct->u.lnk.linkdata_len,
            NFS4_OPAQUE_LIMIT);
        break;
    case NF4BLK:
    case NF4CHR:
        result = xdr_u_int32_t(xdr, &ct->u.devdata.specdata1);
        if (result == TRUE)
            result = xdr_u_int32_t(xdr, &ct->u.devdata.specdata2);
        break;
    default:
        // Some types need no further action
        break;
    }
    return result;
}