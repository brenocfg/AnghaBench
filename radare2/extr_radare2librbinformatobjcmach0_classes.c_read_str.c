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
typedef  int ut32 ;
typedef  scalar_t__ mach0_ut ;
struct TYPE_4__ {int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ RBinFile ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_CLASS_NAME_LEN ; 
 int /*<<< orphan*/  R_FREE (char*) ; 
 int R_MIN (int /*<<< orphan*/ ,int) ; 
 char* calloc (int,int) ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int r_buf_read_at (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  r_return_val_if_fail (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ va2pa (scalar_t__,int*,int*,TYPE_1__*) ; 

__attribute__((used)) static char *read_str(RBinFile *bf, mach0_ut p, ut32 *offset, ut32 *left) {
	r_return_val_if_fail (bf && offset && left, NULL);

	mach0_ut paddr = va2pa (p, offset, left, bf);
	if (paddr == 0 || *left <= 1) {
		return NULL;
	}

	int name_len = R_MIN (MAX_CLASS_NAME_LEN, *left);
	char *name = calloc (1, name_len + 1);
	int len = r_buf_read_at (bf->buf, paddr, (ut8 *)name, name_len);
	if (len < name_len) {
		eprintf ("Error reading\n");
		R_FREE (name);
		return NULL;
	}

	return name;
}