#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_quad_t ;
struct TYPE_7__ {unsigned char* owner; int /*<<< orphan*/  owner_len; } ;
typedef  TYPE_1__ state_owner4 ;
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_8__ {scalar_t__ x_op; } ;
typedef  TYPE_2__ XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NFS4_OPAQUE_LIMIT ; 
 scalar_t__ XDR_DECODE ; 
 scalar_t__ XDR_ENCODE ; 
 int /*<<< orphan*/  xdr_bytes (TYPE_2__*,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_u_hyper (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool_t xdr_state_owner4(
    XDR *xdr,
    state_owner4 *so)
{
    u_quad_t clientid = 0;
    unsigned char *owner = so->owner;

    /* 18.16.3. "The client can set the clientid field to any value and
     * the server MUST ignore it.  Instead the server MUST derive the
     * client ID from the session ID of the SEQUENCE operation of the
     * COMPOUND request. */
    if (xdr->x_op == XDR_ENCODE) {
        if (!xdr_u_hyper(xdr, &clientid)) /* clientid = 0 */
            return FALSE;
    } else if (xdr->x_op == XDR_DECODE) {
        if (!xdr_u_hyper(xdr, &clientid))
            return FALSE;
    } else return FALSE;

    return xdr_bytes(xdr, (char **)&owner, &so->owner_len, NFS4_OPAQUE_LIMIT);
}