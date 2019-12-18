#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_6__ {int /*<<< orphan*/  offset; } ;
struct TYPE_5__ {int /*<<< orphan*/  offset; } ;
struct TYPE_4__ {int /*<<< orphan*/  offset; } ;
typedef  TYPE_1__ TREE_BLOCK_REF ;
typedef  TYPE_2__ SHARED_DATA_REF ;
typedef  TYPE_3__ SHARED_BLOCK_REF ;
typedef  int /*<<< orphan*/  EXTENT_DATA_REF ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,scalar_t__) ; 
 scalar_t__ TYPE_EXTENT_DATA_REF ; 
 scalar_t__ TYPE_SHARED_BLOCK_REF ; 
 scalar_t__ TYPE_SHARED_DATA_REF ; 
 scalar_t__ TYPE_TREE_BLOCK_REF ; 
 int /*<<< orphan*/  get_extent_data_ref_hash (int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint64_t get_extent_hash(uint8_t type, void* data) {
    if (type == TYPE_EXTENT_DATA_REF) {
        return get_extent_data_ref_hash((EXTENT_DATA_REF*)data);
    } else if (type == TYPE_SHARED_BLOCK_REF) {
        SHARED_BLOCK_REF* sbr = (SHARED_BLOCK_REF*)data;
        return sbr->offset;
    } else if (type == TYPE_SHARED_DATA_REF) {
        SHARED_DATA_REF* sdr = (SHARED_DATA_REF*)data;
        return sdr->offset;
    } else if (type == TYPE_TREE_BLOCK_REF) {
        TREE_BLOCK_REF* tbr = (TREE_BLOCK_REF*)data;
        return tbr->offset;
    } else {
        ERR("unhandled extent type %x\n", type);
        return 0;
    }
}