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
typedef  int u8 ;
struct ceph_entity_addr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  bad ; 
 int /*<<< orphan*/  ceph_decode_8_safe (void**,void*,int,int /*<<< orphan*/ ) ; 
 int ceph_decode_entity_addr_legacy (void**,void*,struct ceph_entity_addr*) ; 
 int ceph_decode_entity_addr_versioned (void**,void*,struct ceph_entity_addr*) ; 

int
ceph_decode_entity_addr(void **p, void *end, struct ceph_entity_addr *addr)
{
	u8 marker;

	ceph_decode_8_safe(p, end, marker, bad);
	if (marker == 1)
		return ceph_decode_entity_addr_versioned(p, end, addr);
	else if (marker == 0)
		return ceph_decode_entity_addr_legacy(p, end, addr);
bad:
	return -EINVAL;
}