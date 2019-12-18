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
struct buf_io_priv {int /*<<< orphan*/  fd; TYPE_1__* iob; } ;
typedef  int /*<<< orphan*/  st64 ;
struct TYPE_2__ {int /*<<< orphan*/  io; int /*<<< orphan*/  (* fd_seek ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
#define  R_BUF_CUR 130 
#define  R_BUF_END 129 
#define  R_BUF_SET 128 
 int R_IO_SEEK_CUR ; 
 int R_IO_SEEK_END ; 
 int R_IO_SEEK_SET ; 
 struct buf_io_priv* get_priv_io (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_warn_if_reached () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static st64 buf_io_seek(RBuffer *b, st64 addr, int whence) {
	struct buf_io_priv *priv = get_priv_io (b);
	int io_whence;

	switch (whence) {
	default:
		r_warn_if_reached ();
	case R_BUF_SET:
		io_whence = R_IO_SEEK_SET;
		break;
	case R_BUF_END:
		io_whence = R_IO_SEEK_END;
		break;
	case R_BUF_CUR:
		io_whence = R_IO_SEEK_CUR;
		break;
	}
	return priv->iob->fd_seek (priv->iob->io, priv->fd, addr, io_whence);
}