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
struct TYPE_8__ {scalar_t__ off; } ;
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ RIODesc ;
typedef  TYPE_2__ RIO ;

/* Variables and functions */
 scalar_t__ RIOHTTP_BUF (TYPE_1__*) ; 
 scalar_t__ RIOHTTP_SZ (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int __write(RIO *io, RIODesc *fd, const ut8 *buf, int count) {
	if (!fd || !fd->data) {
		return -1;
	}
	if (io->off + count > RIOHTTP_SZ (fd)) {
		return -1;
	}
	memcpy (RIOHTTP_BUF (fd)+io->off, buf, count);
	return count;
}