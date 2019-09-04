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
struct TYPE_3__ {int /*<<< orphan*/  st_netname; int /*<<< orphan*/  st_pub_key; int /*<<< orphan*/  st_priv_key; } ;
typedef  TYPE_1__ key_netstarg ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  xdr_keybuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_netnamestr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool_t
xdr_key_netstarg(register XDR *xdrs, key_netstarg *objp)
{

	if (!xdr_keybuf(xdrs, objp->st_priv_key))
		return (FALSE);
	if (!xdr_keybuf(xdrs, objp->st_pub_key))
		return (FALSE);
	if (!xdr_netnamestr(xdrs, &objp->st_netname))
		return (FALSE);
	return (TRUE);
}