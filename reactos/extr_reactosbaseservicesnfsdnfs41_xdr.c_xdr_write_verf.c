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
struct TYPE_3__ {scalar_t__ verf; int /*<<< orphan*/  committed; } ;
typedef  TYPE_1__ nfs41_write_verf ;
typedef  int /*<<< orphan*/  enum_t ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NFS4_VERIFIER_SIZE ; 
 int /*<<< orphan*/  xdr_enum (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_opaque (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool_t xdr_write_verf(
    XDR *xdr,
    nfs41_write_verf *verf)
{
    if (!xdr_enum(xdr, (enum_t *)&verf->committed))
        return FALSE;

    return xdr_opaque(xdr, (char *)verf->verf, NFS4_VERIFIER_SIZE);
}