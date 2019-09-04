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
typedef  int /*<<< orphan*/  val ;
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut32 ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  r_buf_write_at (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  r_write_le32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __patch_reloc(RBuffer *buf, ut32 addr_to_patch, ut32 data_offset) {
	ut8 val[4] = {
		0
	};
	r_write_le32 (val, data_offset);
	r_buf_write_at (buf, addr_to_patch, (void *) val, sizeof (val));
}