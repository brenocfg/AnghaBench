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
struct ceph_pg {int seed; int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  ceph_encode_32 (void**,int) ; 
 int /*<<< orphan*/  ceph_encode_64 (void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_encode_8 (void**,int) ; 

__attribute__((used)) static void encode_pgid(void **p, const struct ceph_pg *pgid)
{
	ceph_encode_8(p, 1);
	ceph_encode_64(p, pgid->pool);
	ceph_encode_32(p, pgid->seed);
	ceph_encode_32(p, -1); /* preferred */
}