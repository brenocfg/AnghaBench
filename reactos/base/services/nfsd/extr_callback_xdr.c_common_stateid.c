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
struct TYPE_3__ {scalar_t__ other; int /*<<< orphan*/  seqid; } ;
typedef  TYPE_1__ stateid4 ;
typedef  int bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  NFS4_STATEID_OTHER ; 
 scalar_t__ xdr_opaque (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ xdr_u_int32_t (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool_t common_stateid(XDR *xdr, stateid4 *stateid)
{
    return xdr_u_int32_t(xdr, &stateid->seqid)
        && xdr_opaque(xdr, (char*)stateid->other, NFS4_STATEID_OTHER);
}