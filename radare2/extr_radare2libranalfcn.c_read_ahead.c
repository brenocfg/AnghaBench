#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  scalar_t__ ut64 ;
typedef  int /*<<< orphan*/  cache ;
struct TYPE_4__ {int (* read_at ) (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int) ;int /*<<< orphan*/  io; } ;
struct TYPE_5__ {TYPE_1__ iob; } ;
typedef  TYPE_2__ RAnal ;

/* Variables and functions */
 scalar_t__ UT64_ADD_OVFCHK (scalar_t__,int const) ; 
 scalar_t__ UT64_MAX ; 
 scalar_t__ cache_addr ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int const) ; 
 int stub1 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int stub2 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int read_ahead(RAnal *anal, ut64 addr, ut8 *buf, int len) {
	static ut8 cache[1024];
	const int cache_len = sizeof (cache);

	if (len < 1) {
		return 0;
	}
	if (len > cache_len) {
		int a = anal->iob.read_at (anal->iob.io, addr, buf, len); // double read
		memcpy (cache, buf, cache_len);
		cache_addr = addr;
		return a;
	}

	ut64 addr_end = UT64_ADD_OVFCHK (addr, len)? UT64_MAX: addr + len;
	ut64 cache_addr_end = UT64_ADD_OVFCHK (cache_addr, cache_len)? UT64_MAX: cache_addr + cache_len;
	bool isCached = ((addr != UT64_MAX) && (addr >= cache_addr) && (addr_end < cache_addr_end));
	if (isCached) {
		memcpy (buf, cache + (addr - cache_addr), len);
	} else {
		anal->iob.read_at (anal->iob.io, addr, cache, sizeof (cache));
		memcpy (buf, cache, len);
		cache_addr = addr;
	}
	return len;
}