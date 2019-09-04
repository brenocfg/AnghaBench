#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_2__ {int /*<<< orphan*/  f_opthdr; } ;
struct r_bin_coff_obj {scalar_t__ endian; int /*<<< orphan*/  opt_hdr; int /*<<< orphan*/  b; TYPE_1__ hdr; } ;
struct coff_opt_hdr {int dummy; } ;
struct coff_hdr {int dummy; } ;

/* Variables and functions */
 int r_buf_fread_at (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static bool r_bin_coff_init_opt_hdr(struct r_bin_coff_obj *obj) {
	int ret;
	if (!obj->hdr.f_opthdr) {
		return false;
	}
	ret = r_buf_fread_at (obj->b, sizeof (struct coff_hdr), 
						 (ut8 *)&obj->opt_hdr, obj->endian? "2S6I": "2s6i", 1);
	if (ret != sizeof (struct coff_opt_hdr)) {
		return false;
	}
	return true;
}