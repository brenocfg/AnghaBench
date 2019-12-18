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
typedef  int ut64 ;
struct TYPE_2__ {int f_symptr; int f_nsyms; } ;
struct r_bin_coff_obj {int size; scalar_t__ symbols; TYPE_1__ hdr; scalar_t__ endian; int /*<<< orphan*/  b; } ;
struct coff_symbol {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  R_FREE (scalar_t__) ; 
 scalar_t__ calloc (int,int) ; 
 int r_buf_fread_at (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static bool r_bin_coff_init_symtable(struct r_bin_coff_obj *obj) {
	int ret, size;
	ut64 offset = obj->hdr.f_symptr;
	if (obj->hdr.f_nsyms >= 0xffff || !obj->hdr.f_nsyms) { // too much symbols, probably not allocatable
		return false;
	}
	size = obj->hdr.f_nsyms * sizeof (struct coff_symbol);
	if (size < 0 ||
		size > obj->size ||
		offset > obj->size ||
		offset + size > obj->size) {
		return false;
	} 
	obj->symbols = calloc (1, size + sizeof (struct coff_symbol));
	if (!obj->symbols) {
		return false;
	}
	ret = r_buf_fread_at (obj->b, offset, (ut8 *)obj->symbols, obj->endian? "8c1I2S2c": "8c1i2s2c", obj->hdr.f_nsyms);
	if (ret != size) {
		R_FREE (obj->symbols);
		return false;
	}
	return true;
}