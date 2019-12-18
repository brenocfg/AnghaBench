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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int CEPH_ENTITY_TYPE_CLIENT ; 
 int ERANGE ; 
 int /*<<< orphan*/  ceph_encode_32 (void**,int) ; 
 int /*<<< orphan*/  ceph_encode_copy (void**,char const*,int) ; 
 int strlen (char const*) ; 

int ceph_auth_entity_name_encode(const char *name, void **p, void *end)
{
	int len = strlen(name);

	if (*p + 2*sizeof(u32) + len > end)
		return -ERANGE;
	ceph_encode_32(p, CEPH_ENTITY_TYPE_CLIENT);
	ceph_encode_32(p, len);
	ceph_encode_copy(p, name, len);
	return 0;
}