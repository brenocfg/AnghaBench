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
struct TYPE_3__ {int /*<<< orphan*/  deskey; int /*<<< orphan*/  remotename; } ;
typedef  TYPE_1__ cryptkeyarg ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  xdr_des_block (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_netnamestr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool_t
xdr_cryptkeyarg(register XDR *xdrs, cryptkeyarg *objp)
{

	if (!xdr_netnamestr(xdrs, &objp->remotename))
		return (FALSE);
	if (!xdr_des_block(xdrs, &objp->deskey))
		return (FALSE);
	return (TRUE);
}