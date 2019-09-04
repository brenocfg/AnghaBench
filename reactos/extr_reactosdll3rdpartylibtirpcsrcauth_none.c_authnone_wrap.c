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
typedef  int (* xdrproc_t ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int /*<<< orphan*/  XDR ;
typedef  int /*<<< orphan*/  AUTH ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
authnone_wrap(AUTH *auth, XDR *xdrs, xdrproc_t func, caddr_t args)
{
    return ((*func)(xdrs, args));
}