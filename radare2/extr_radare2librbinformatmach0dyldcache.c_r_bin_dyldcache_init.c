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
struct TYPE_2__ {int /*<<< orphan*/  numlibs; } ;
struct r_bin_dyldcache_obj_t {TYPE_1__ hdr; int /*<<< orphan*/  nlibs; int /*<<< orphan*/  b; } ;

/* Variables and functions */
 int /*<<< orphan*/  perror (char*) ; 
 int r_buf_fread_at (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int r_bin_dyldcache_init(struct r_bin_dyldcache_obj_t* bin) {
	int len = r_buf_fread_at (bin->b, 0, (ut8*)&bin->hdr, "16c4i7l", 1);
	if (len == -1) {
		perror ("read (cache_header)");
		return false;
	}
	bin->nlibs = bin->hdr.numlibs;
	return true;
}