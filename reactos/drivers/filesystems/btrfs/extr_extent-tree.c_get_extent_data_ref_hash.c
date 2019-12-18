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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  objid; int /*<<< orphan*/  root; } ;
typedef  TYPE_1__ EXTENT_DATA_REF ;

/* Variables and functions */
 int /*<<< orphan*/  get_extent_data_ref_hash2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline uint64_t get_extent_data_ref_hash(EXTENT_DATA_REF* edr) {
    return get_extent_data_ref_hash2(edr->root, edr->objid, edr->offset);
}