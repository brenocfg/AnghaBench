#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  scalar_t__ ut32 ;
struct TYPE_6__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ RIODesc ;
typedef  int /*<<< orphan*/  RIO ;

/* Variables and functions */
 scalar_t__ _io_malloc_buf (TYPE_1__*) ; 
 scalar_t__ _io_malloc_off (TYPE_1__*) ; 
 scalar_t__ _io_malloc_sz (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int __read(RIO *io, RIODesc *fd, ut8 *buf, int count) {
	memset (buf, 0xff, count);
	if (!fd || !fd->data) {
		return -1;
	}
	ut32 mallocsz = _io_malloc_sz (fd);
	if (_io_malloc_off (fd) > mallocsz) {
		return -1;
	}
	if (_io_malloc_off (fd) + count >= mallocsz) {
		count = mallocsz - _io_malloc_off (fd);
	}
	memcpy (buf, _io_malloc_buf (fd) + _io_malloc_off (fd), count);
	return count;
}