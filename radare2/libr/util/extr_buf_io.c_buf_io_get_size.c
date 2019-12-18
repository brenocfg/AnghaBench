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
typedef  int /*<<< orphan*/  ut64 ;
struct buf_io_priv {int /*<<< orphan*/  fd; TYPE_1__* iob; } ;
struct TYPE_2__ {int /*<<< orphan*/  io; int /*<<< orphan*/  (* fd_size ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 struct buf_io_priv* get_priv_io (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ut64 buf_io_get_size(RBuffer *b) {
	struct buf_io_priv *priv = get_priv_io (b);
	return priv->iob->fd_size (priv->iob->io, priv->fd);
}