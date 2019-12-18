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
typedef  int /*<<< orphan*/  nfsacl41 ;
struct TYPE_3__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ XDR ;

/* Variables and functions */
 int /*<<< orphan*/  XDR_FREE ; 
 int /*<<< orphan*/  xdr_nfsacl41 (TYPE_1__*,int /*<<< orphan*/ *) ; 

void nfsacl41_free(nfsacl41 *acl)
{
    XDR xdr = { XDR_FREE };
    xdr_nfsacl41(&xdr, acl);
}