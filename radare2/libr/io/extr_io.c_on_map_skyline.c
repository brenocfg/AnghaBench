#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  scalar_t__ ut64 ;
typedef  scalar_t__ st64 ;
typedef  scalar_t__ (* cbOnIterMap ) (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,scalar_t__,TYPE_3__*,int /*<<< orphan*/ *) ;
struct TYPE_15__ {scalar_t__ addr; } ;
struct TYPE_14__ {TYPE_3__* map; TYPE_7__ itv; } ;
struct TYPE_11__ {scalar_t__ addr; } ;
struct TYPE_13__ {int perm; scalar_t__ delta; TYPE_1__ itv; int /*<<< orphan*/  fd; } ;
struct TYPE_12__ {scalar_t__ p_cache; int /*<<< orphan*/  map_skyline; } ;
typedef  int /*<<< orphan*/  RPVector ;
typedef  TYPE_4__ RIOMapSkyline ;
typedef  TYPE_2__ RIO ;

/* Variables and functions */
 int /*<<< orphan*/  CMP ; 
 scalar_t__ R_MIN (scalar_t__,scalar_t__) ; 
 int r_itv_end (TYPE_7__) ; 
 TYPE_4__* r_pvector_at (int /*<<< orphan*/  const*,size_t) ; 
 size_t r_pvector_len (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  r_pvector_lower_bound (int /*<<< orphan*/  const*,scalar_t__,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static st64 on_map_skyline(RIO *io, ut64 vaddr, ut8 *buf, int len, int match_flg, cbOnIterMap op, bool prefix_mode) {
	const RPVector *skyline = &io->map_skyline;
	ut64 addr = vaddr;
	size_t i;
	bool ret = true, wrap = !prefix_mode && vaddr + len < vaddr;
#define CMP(addr, part) ((addr) < r_itv_end (((RIOMapSkyline *)(part))->itv) - 1 ? -1 : \
			(addr) > r_itv_end (((RIOMapSkyline *)(part))->itv) - 1 ? 1 : 0)
	// Let i be the first skyline part whose right endpoint > addr
	if (!len) {
		i = r_pvector_len (skyline);
	} else {
		r_pvector_lower_bound (skyline, addr, i, CMP);
		if (i == r_pvector_len (skyline) && wrap) {
			wrap = false;
			i = 0;
			addr = 0;
		}
	}
#undef CMP
	while (i < r_pvector_len (skyline)) {
		const RIOMapSkyline *part = r_pvector_at (skyline, i);
		// Right endpoint <= addr
		if (r_itv_end (part->itv) - 1 < addr) {
			i++;
			if (wrap && i == r_pvector_len (skyline)) {
				wrap = false;
				i = 0;
				addr = 0;
			}
			continue;
		}
		if (addr < part->itv.addr) {
			// [addr, part->itv.addr) is a gap
			if (prefix_mode || len <= part->itv.addr - vaddr) {
				break;
			}
			addr = part->itv.addr;
		}
		// Now left endpoint <= addr < right endpoint
		ut64 len1 = R_MIN (vaddr + len - addr, r_itv_end (part->itv) - addr);
		if (len1 < 1) {
			break;
		}
		// The map satisfies the permission requirement or p_cache is enabled
		if (((part->map->perm & match_flg) == match_flg || io->p_cache)) {
			st64 result = op (io, part->map->fd, part->map->delta + addr - part->map->itv.addr,
					buf + (addr - vaddr), len1, part->map, NULL);
			if (prefix_mode) {
				if (result < 0) {
					return result;
				}
				addr += result;
				if (result != len1) {
					break;
				}
			} else {
				if (result != len1) {
					ret = false;
				}
				addr += len1;
			}
		} else if (prefix_mode) {
			break;
		} else {
			addr += len1;
			ret = false;
		}
		// Reaches the end
		if (addr == vaddr + len) {
			break;
		}
		// Wrap to the beginning of skyline if address wraps
		if (!addr) {
			i = 0;
		}
	}
	return prefix_mode ? addr - vaddr : ret;
}