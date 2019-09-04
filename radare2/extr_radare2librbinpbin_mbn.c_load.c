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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_6__ {int /*<<< orphan*/  sdb; TYPE_1__* o; scalar_t__ buf; } ;
struct TYPE_5__ {int /*<<< orphan*/  loadaddr; int /*<<< orphan*/  bin_obj; } ;
typedef  TYPE_2__ RBinFile ;

/* Variables and functions */
 int load_bytes (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * r_buf_buffer (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool load(RBinFile *bf) {
	if (bf && bf->buf) {
		ut64 sz;
		const ut8 *bytes = r_buf_buffer (bf->buf, &sz);
		return load_bytes (bf, &bf->o->bin_obj, bytes, sz, bf->o->loadaddr, bf->sdb);
	}
	return false;
}