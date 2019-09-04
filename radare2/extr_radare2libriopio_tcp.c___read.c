#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_8__ {unsigned int off; } ;
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ RIODesc ;
typedef  TYPE_2__ RIO ;

/* Variables and functions */
 scalar_t__ RIOTCP_BUF (TYPE_1__*) ; 
 unsigned int RIOTCP_SZ (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static int __read(RIO *io, RIODesc *fd, ut8 *buf, int count) {
	unsigned int sz;
	if (!fd || !fd->data) {
		return -1;
	}
	sz = RIOTCP_SZ (fd);
	if (io->off >= sz) {
		return -1;
	}
	if (io->off + count >= sz) {
		count = sz - io->off;
	}
	memcpy (buf, RIOTCP_BUF (fd) + io->off, count);
	return count;
}