#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  scalar_t__ ut64 ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_5__ {int fd_priv; scalar_t__ cur_priv; scalar_t__ base_priv; scalar_t__ offset_priv; int /*<<< orphan*/ * buf_priv; scalar_t__ iob; scalar_t__ empty_priv; } ;
typedef  TYPE_1__ RBuffer ;

/* Variables and functions */
 scalar_t__ R_BUF_CUR ; 
 scalar_t__ UT64_MAX ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  r_buf_read_at (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *,int) ; 
 scalar_t__ r_buf_size (TYPE_1__*) ; 

__attribute__((used)) static ut8 *r_buf_get_at(RBuffer *b, ut64 addr, int *left) {
	if (b->empty_priv) {
		return NULL;
	}
	if (b->iob) {
		if (b->fd_priv != -1) {
			eprintf ("r_buf_get_at not supported for r_buf_new_file\n");
			return NULL;
		}
		static ut8 buf[8];
		r_buf_read_at (b, addr, buf, sizeof (buf));
		if (left) {
			*left = 8;
		}
		return buf;
	}
	if (addr == R_BUF_CUR) {
		addr = b->cur_priv;
	} else {
		addr = addr - b->base_priv + b->offset_priv;
	}
	ut64 effective_size = r_buf_size (b);
	if (addr == UT64_MAX || addr - b->offset_priv > effective_size) {
		return NULL;
	}
	if (left) {
		*left = effective_size - addr + b->offset_priv;
	}
	return b->buf_priv + addr;
}