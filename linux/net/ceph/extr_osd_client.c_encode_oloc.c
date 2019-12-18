#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ceph_object_locator {TYPE_1__* pool_ns; int /*<<< orphan*/  pool; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/  str; } ;

/* Variables and functions */
 int /*<<< orphan*/  ceph_encode_32 (void**,int) ; 
 int /*<<< orphan*/  ceph_encode_64 (void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_encode_string (void**,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_oloc_encoding_size (struct ceph_object_locator const*) ; 
 int /*<<< orphan*/  ceph_start_encoding (void**,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void encode_oloc(void **p, void *end,
			const struct ceph_object_locator *oloc)
{
	ceph_start_encoding(p, 5, 4, ceph_oloc_encoding_size(oloc));
	ceph_encode_64(p, oloc->pool);
	ceph_encode_32(p, -1); /* preferred */
	ceph_encode_32(p, 0);  /* key len */
	if (oloc->pool_ns)
		ceph_encode_string(p, end, oloc->pool_ns->str,
				   oloc->pool_ns->len);
	else
		ceph_encode_32(p, 0);
}