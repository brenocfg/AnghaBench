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
typedef  int /*<<< orphan*/  xdrproc_t ;
struct TYPE_3__ {int /*<<< orphan*/  count; int /*<<< orphan*/  aces; } ;
typedef  TYPE_1__ nfsacl41 ;
typedef  int /*<<< orphan*/  nfsace4 ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  xdr_array (int /*<<< orphan*/ *,char**,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ xdr_nfsace4 ; 

__attribute__((used)) static bool_t xdr_nfsacl41(
    XDR *xdr,
    nfsacl41 *acl)
{
    return xdr_array(xdr, (char**)&acl->aces, &acl->count,
        32, sizeof(nfsace4), (xdrproc_t)xdr_nfsace4);
}