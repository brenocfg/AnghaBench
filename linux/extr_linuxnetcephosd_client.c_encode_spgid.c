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
struct ceph_spg {int /*<<< orphan*/  shard; int /*<<< orphan*/  pgid; } ;

/* Variables and functions */
 scalar_t__ CEPH_PGID_ENCODING_LEN ; 
 int /*<<< orphan*/  ceph_encode_8 (void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_start_encoding (void**,int,int,scalar_t__) ; 
 int /*<<< orphan*/  encode_pgid (void**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void encode_spgid(void **p, const struct ceph_spg *spgid)
{
	ceph_start_encoding(p, 1, 1, CEPH_PGID_ENCODING_LEN + 1);
	encode_pgid(p, &spgid->pgid);
	ceph_encode_8(p, spgid->shard);
}