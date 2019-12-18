#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int ut8 ;
struct TYPE_7__ {int data_len; int /*<<< orphan*/  data; } ;
struct TYPE_6__ {int /*<<< orphan*/  reg; } ;
typedef  TYPE_1__ RDebug ;

/* Variables and functions */
 int R_DEBUG_REASON_UNKNOWN ; 
 int R_MAX (int,int) ; 
 int R_MIN (int,int) ; 
 int buf_size ; 
 int* calloc (int,int) ; 
 int /*<<< orphan*/  check_connection (TYPE_1__*) ; 
 TYPE_3__* desc ; 
 int /*<<< orphan*/  eprintf (char*,int,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdbr_read_registers (TYPE_3__*) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  r_reg_get_bytes (int /*<<< orphan*/ ,int,int*) ; 
 int* realloc (int*,int) ; 
 int* reg_buf ; 

__attribute__((used)) static int r_debug_gdb_reg_read(RDebug *dbg, int type, ut8 *buf, int size) {
	int copy_size;
	int buflen = 0;
	check_connection (dbg);
	if (!desc) {
		return R_DEBUG_REASON_UNKNOWN;
	}
	gdbr_read_registers (desc);
	if (!desc || !desc->data) {
		return -1;
	}
	// read the len of the current area
	free (r_reg_get_bytes (dbg->reg, type, &buflen));
	if (size < desc->data_len) {
		eprintf ("r_debug_gdb_reg_read: small buffer %d vs %d\n",
			(int)size, (int)desc->data_len);
		//	return -1;
	}
	copy_size = R_MIN (desc->data_len, size);
	buflen = R_MAX (desc->data_len, buflen);
	if (reg_buf) {
		// if (buf_size < copy_size) { //desc->data_len) {
		if (buflen > buf_size) { //copy_size) {
			ut8* new_buf = realloc (reg_buf, buflen);
			if (!new_buf) {
				return -1;
			}
			reg_buf = new_buf;
			buf_size = buflen;
		}
	} else {
		reg_buf = calloc (buflen, 1);
		if (!reg_buf) {
			return -1;
		}
		buf_size = buflen;
	}
	memset ((void*)(volatile void*)buf, 0, size);
	memcpy ((void*)(volatile void*)buf, desc->data, R_MIN (copy_size, size));
	memset ((void*)(volatile void*)reg_buf, 0, buflen);
	memcpy ((void*)(volatile void*)reg_buf, desc->data, copy_size);
#if 0
	int i;
	//for(i=0;i<168;i++) {
	for(i=0;i<copy_size;i++) {
		if (!(i%16)) printf ("\n0x%08x  ", i);
		printf ("%02x ", buf[i]); //(ut8)desc->data[i]);
	}
	printf("\n");
#endif
	return desc->data_len;
}