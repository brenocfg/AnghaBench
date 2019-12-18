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
typedef  int ut64 ;
struct ht_rel_t {int k; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_6__ {scalar_t__ endian; int /*<<< orphan*/  b; } ;
struct TYPE_5__ {int /*<<< orphan*/  offset; } ;
typedef  TYPE_1__ RBinElfSection ;
typedef  TYPE_2__ ELFOBJ ;

/* Variables and functions */
 int r_buf_read_at (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int r_read_be32 (int /*<<< orphan*/ *) ; 
 int r_read_le32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ut64 get_import_addr_ppc(ELFOBJ *bin, struct ht_rel_t *rel, RBinElfSection *plt_section, int nrel) {
	ut8 buf[4] = { 0 };
	if (!plt_section) {
		return -1;
	}
	int len = r_buf_read_at (bin->b, plt_section->offset, buf, sizeof (buf));
	if (len < 4) {
		return -1;
	}

	if (bin->endian) {
		ut64 base = r_read_be32 (buf);
		base -= (nrel * 16);
		base += (rel->k * 16);
		return base;
	}
	// FIXME: this does not seem to work as
	// expected. Commenting for now because it makes
	// refactoring much easier and it seems weird
	// anyway.
	// if (bin->is_rela == DT_RELA) {
	// 	len = r_buf_read_at (bin->b, rel_sec->offset, buf, sizeof (buf));
	// 	if (len < 4) {
	// 		goto out;
	//	}
	// }
	ut64 base = r_read_le32 (buf);
	base -= (nrel * 12) + 20;
	base += (rel->k * 8);
	return base;
}