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
struct intel_bts_snapshot_ref {int dummy; } ;
struct intel_bts_recording {int snapshot_ref_cnt; struct intel_bts_snapshot_ref* snapshot_refs; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct intel_bts_snapshot_ref* calloc (int,size_t const) ; 
 int /*<<< orphan*/  memcpy (struct intel_bts_snapshot_ref*,struct intel_bts_snapshot_ref*,int) ; 

__attribute__((used)) static int intel_bts_alloc_snapshot_refs(struct intel_bts_recording *btsr,
					 int idx)
{
	const size_t sz = sizeof(struct intel_bts_snapshot_ref);
	int cnt = btsr->snapshot_ref_cnt, new_cnt = cnt * 2;
	struct intel_bts_snapshot_ref *refs;

	if (!new_cnt)
		new_cnt = 16;

	while (new_cnt <= idx)
		new_cnt *= 2;

	refs = calloc(new_cnt, sz);
	if (!refs)
		return -ENOMEM;

	memcpy(refs, btsr->snapshot_refs, cnt * sz);

	btsr->snapshot_refs = refs;
	btsr->snapshot_ref_cnt = new_cnt;

	return 0;
}