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
struct xdr_netobj {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 unsigned int OWNER_HASH_MASK ; 
 unsigned int opaque_hashval (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int ownerstr_hashval(struct xdr_netobj *ownername)
{
	unsigned int ret;

	ret = opaque_hashval(ownername->data, ownername->len);
	return ret & OWNER_HASH_MASK;
}