#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  scalar_t__ ut64 ;
struct TYPE_7__ {scalar_t__ base_priv; scalar_t__ offset_priv; int fd_priv; scalar_t__ cur_priv; scalar_t__ sparse_priv; int /*<<< orphan*/  Oxff_priv; TYPE_1__* iob; scalar_t__ empty_priv; } ;
struct TYPE_6__ {int (* fd_write_at ) (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/  const*,int) ;int (* fd_read_at ) (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ *,int) ;int (* write_at ) (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/  const*,int) ;int (* read_at ) (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int) ;int /*<<< orphan*/  io; } ;
typedef  TYPE_1__ RIOBind ;
typedef  TYPE_2__ RBuffer ;

/* Variables and functions */
 scalar_t__ R_BUF_CUR ; 
 int R_MIN (int,scalar_t__) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ r_buf_size (TYPE_2__*) ; 
 int /*<<< orphan*/  r_return_val_if_fail (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int r_sandbox_lseek (int,scalar_t__,int /*<<< orphan*/ ) ; 
 int r_sandbox_read (int,int /*<<< orphan*/ *,int) ; 
 int r_sandbox_write (int,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  sparse_read (scalar_t__,scalar_t__,int /*<<< orphan*/ *,int) ; 
 scalar_t__ sparse_write (scalar_t__,scalar_t__,int /*<<< orphan*/  const*,int) ; 
 int stub1 (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/  const*,int) ; 
 int stub2 (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int stub3 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/  const*,int) ; 
 int stub4 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int r_buf_cpy(RBuffer *b, ut64 addr, ut8 *dst, const ut8 *src, int len, int write) {
	r_return_val_if_fail (b, 0);

	if (b->empty_priv) {
		return 0;
	}

	ut64 start = addr - b->base_priv + b->offset_priv;
	ut64 effective_size = r_buf_size (b);
	int real_len = len;
	if (start - b->offset_priv + len > effective_size) {
		real_len = effective_size - start + b->offset_priv;
	}
	if (real_len < 1) {
		return 0;
	}
	if (b->iob) {
		RIOBind *iob = b->iob;
		if (b->fd_priv != -1) {
			return write
				? iob->fd_write_at (iob->io, b->fd_priv, start, src, real_len)
				: iob->fd_read_at (iob->io, b->fd_priv, start, dst, real_len);
		}
		return write
			? iob->write_at (iob->io, start, src, real_len)
			: iob->read_at (iob->io, start, dst, real_len);
	}
	if (b->fd_priv != -1) {
		if (r_sandbox_lseek (b->fd_priv, start, SEEK_SET) == -1) {
			// seek failed - print error here?
			// return 0;
		}
		if (write) {
			return r_sandbox_write (b->fd_priv, src, real_len);
		}
		memset (dst, 0, real_len);
		return r_sandbox_read (b->fd_priv, dst, real_len);
	}
	if (b->sparse_priv) {
		if (write) {
			// create new with src + len
			if (sparse_write (b->sparse_priv, start, src, real_len) < 0) {
				return -1;
			}
		} else {
			// read from sparse and write into dst
			memset (dst, b->Oxff_priv, len);
			(void)sparse_read (b->sparse_priv, start, dst, real_len);
			len = R_MIN (real_len , r_buf_size (b) - addr);
		}
		return real_len;
	}
	addr = (addr == R_BUF_CUR)? b->cur_priv: start;
	if (len < 1 || !dst || addr - b->offset_priv > effective_size) {
		return -1;
	}
	if (write) {
		dst += addr;
	} else {
		src += addr;
	}
	memmove (dst, src, real_len);
	b->cur_priv = addr + real_len;
	return real_len;
}