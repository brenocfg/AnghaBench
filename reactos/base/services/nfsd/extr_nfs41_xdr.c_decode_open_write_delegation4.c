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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {int /*<<< orphan*/  permissions; int /*<<< orphan*/  recalled; int /*<<< orphan*/  stateid; } ;
typedef  TYPE_1__ open_delegation4 ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  decode_space_limit4 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_bool (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_nfsace4 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_stateid4 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool_t decode_open_write_delegation4(
    XDR *xdr,
    open_delegation4 *delegation)
{
    uint64_t size_limit;

    if (!xdr_stateid4(xdr, &delegation->stateid))
        return FALSE;

    if (!xdr_bool(xdr, &delegation->recalled))
        return FALSE;

    if (!decode_space_limit4(xdr, &size_limit))
        return FALSE;

    return xdr_nfsace4(xdr, &delegation->permissions);
}