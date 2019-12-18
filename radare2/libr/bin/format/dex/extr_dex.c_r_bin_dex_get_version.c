#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_4__ {int /*<<< orphan*/  b; } ;
typedef  TYPE_1__ RBinDexObj ;

/* Variables and functions */
 char* calloc (int,int) ; 
 int /*<<< orphan*/  r_buf_read_at (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  r_return_val_if_fail (TYPE_1__*,int /*<<< orphan*/ *) ; 

char* r_bin_dex_get_version(RBinDexObj *bin) {
	r_return_val_if_fail (bin, NULL);
	char* version = calloc (1, 8);
	if (version) {
		r_buf_read_at (bin->b, 4, (ut8*)version, 3);
		return version;
	}
	return NULL;
}