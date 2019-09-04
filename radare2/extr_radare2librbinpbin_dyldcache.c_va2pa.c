#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut64 ;
typedef  scalar_t__ ut32 ;
typedef  scalar_t__ uint64_t ;
typedef  size_t uint32_t ;
struct TYPE_5__ {scalar_t__ address; scalar_t__ size; scalar_t__ fileOffset; } ;
typedef  TYPE_1__ cache_map_t ;
struct TYPE_6__ {size_t mappingCount; } ;
typedef  TYPE_2__ cache_hdr_t ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 scalar_t__ UT64_MAX ; 

__attribute__((used)) static ut64 va2pa(uint64_t addr, cache_hdr_t *hdr, cache_map_t *maps, RBuffer *cache_buf, ut64 slide, ut32 *offset, ut32 *left) {
	ut64 res = UT64_MAX;
	uint32_t i;

	addr -= slide;

	for (i = 0; i < hdr->mappingCount; ++i) {
		if (addr >= maps[i].address && addr < maps[i].address + maps[i].size) {
			res = maps[i].fileOffset + addr - maps[i].address;
			if (offset) {
				*offset = addr - maps[i].address;
			}
			if (left) {
				*left = maps[i].size - (addr - maps[i].address);
			}
			break;
		}
	}

	return res;
}