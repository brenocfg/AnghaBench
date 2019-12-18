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
struct notify4 {int /*<<< orphan*/  len; int /*<<< orphan*/  list; int /*<<< orphan*/  mask; } ;
typedef  int bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  NFS4_OPAQUE_LIMIT ; 
 scalar_t__ xdr_bitmap4 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ xdr_bytes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool_t common_notify4(XDR *xdr, struct notify4 *notify)
{
    return xdr_bitmap4(xdr, &notify->mask)
        && xdr_bytes(xdr, &notify->list, &notify->len, NFS4_OPAQUE_LIMIT);
}