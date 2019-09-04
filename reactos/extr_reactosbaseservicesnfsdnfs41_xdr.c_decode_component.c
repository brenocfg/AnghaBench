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
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {unsigned short len; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ nfs41_component ;
typedef  scalar_t__ bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  NFS4_OPAQUE_LIMIT ; 
 scalar_t__ xdr_bytes (int /*<<< orphan*/ *,char**,scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool_t decode_component(
    XDR *xdr,
    nfs41_component *component)
{
    bool_t result;
    uint32_t len;

    result = xdr_bytes(xdr, (char **)&component->name, &len, NFS4_OPAQUE_LIMIT);
    component->len = (result == FALSE) ? 0 : (unsigned short)len;
    return result;
}