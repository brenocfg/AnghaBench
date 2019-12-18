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
typedef  int ut32 ;
struct TYPE_2__ {int f_symptr; int f_nsyms; } ;
struct r_bin_coff_obj {int size; int /*<<< orphan*/  b; TYPE_1__ hdr; } ;
struct coff_symbol {int dummy; } ;
typedef  int /*<<< orphan*/  n ;

/* Variables and functions */
 int r_buf_read_at (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 char* r_str_ndup (char*,int) ; 
 char* strdup (char*) ; 

char *r_coff_symbol_name(struct r_bin_coff_obj *obj, void *ptr) {
	char n[256] = {0};
	int len = 0, offset = 0;
	union { 
		char name[8]; 
		struct { 
			ut32 zero; 
			ut32 offset; 
		}; 
	} *p = ptr;
	if (!ptr) {
		return NULL;
	}
	if (p->zero) {
		return r_str_ndup (p->name, 8);
	}
	offset = obj->hdr.f_symptr + obj->hdr.f_nsyms * sizeof (struct coff_symbol) + p->offset;
	if (offset > obj->size) {
		return NULL;
	}
	len = r_buf_read_at (obj->b, offset, (ut8*)n, sizeof (n));
	if (len < 1) {
		return NULL;
	}
	/* ensure null terminated string */
	n[sizeof (n) - 1] = 0;
	return strdup (n);
}