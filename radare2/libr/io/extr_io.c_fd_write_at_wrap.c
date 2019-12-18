#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
typedef  int /*<<< orphan*/  RIOMap ;
typedef  int /*<<< orphan*/  RIO ;

/* Variables and functions */
 int r_io_fd_write_at (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int fd_write_at_wrap (RIO *io, int fd, ut64 addr, ut8 *buf, int len, RIOMap *map, void *user) {
	return r_io_fd_write_at (io, fd, addr, buf, len);
}