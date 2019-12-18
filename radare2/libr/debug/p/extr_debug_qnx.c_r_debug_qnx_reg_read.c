#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_6__ {int /*<<< orphan*/  data; } ;
struct TYPE_8__ {TYPE_1__ recv; } ;
struct TYPE_7__ {int /*<<< orphan*/  reg; } ;
typedef  TYPE_2__ RDebug ;

/* Variables and functions */
 int R_MAX (int,int) ; 
 int R_MIN (int,int) ; 
 int buf_size ; 
 int /*<<< orphan*/ * calloc (int,int) ; 
 TYPE_4__* desc ; 
 int /*<<< orphan*/  eprintf (char*,int,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int qnxr_read_registers (TYPE_4__*) ; 
 int /*<<< orphan*/  r_reg_get_bytes (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * reg_buf ; 

__attribute__((used)) static int r_debug_qnx_reg_read (RDebug *dbg, int type, ut8 *buf, int size) {
	int copy_size;
	int buflen = 0;
	if (!desc) {
		return -1;
	}
	int len = qnxr_read_registers (desc);
	if (len <= 0) {
		return -1;
	}
	// read the len of the current area
	free (r_reg_get_bytes (dbg->reg, type, &buflen));
	if (size < len) {
		eprintf ("r_debug_qnx_reg_read: small buffer %d vs %d\n",
			 (int)size, (int)len);
	}
	copy_size = R_MIN (len, size);
	buflen = R_MAX (len, buflen);
	if (reg_buf) {
		if (buf_size < copy_size) {
			ut8 *new_buf = realloc (reg_buf, copy_size);
			if (!new_buf) {
				return -1;
			}
			reg_buf = new_buf;
			buflen = copy_size;
			buf_size = len;
		}
	} else {
		reg_buf = calloc (buflen, 1);
		if (!reg_buf) {
			return -1;
		}
		buf_size = buflen;
	}
	memset ((void *)(volatile void *) buf, 0, size);
	memcpy ((void *)(volatile void *) buf, desc->recv.data, copy_size);
	memset ((void *)(volatile void *) reg_buf, 0, buflen);
	memcpy ((void *)(volatile void *) reg_buf, desc->recv.data, copy_size);

	return len;
}