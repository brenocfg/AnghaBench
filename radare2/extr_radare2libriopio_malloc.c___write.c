#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ RIODesc ;
typedef  int /*<<< orphan*/  RIO ;

/* Variables and functions */
 scalar_t__ _io_malloc_buf (TYPE_1__*) ; 
 scalar_t__ _io_malloc_off (TYPE_1__*) ; 
 int /*<<< orphan*/  _io_malloc_set_off (TYPE_1__*,scalar_t__) ; 
 scalar_t__ _io_malloc_sz (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int __write(RIO *io, RIODesc *fd, const ut8 *buf, int count) {
	if (!fd || !buf || count < 0 || !fd->data) {
		return -1;
	}
	if (_io_malloc_off (fd) > _io_malloc_sz (fd)) {
		return -1;
	}
	if (_io_malloc_off (fd) + count > _io_malloc_sz (fd)) {
		count -= (_io_malloc_off (fd) + count -_io_malloc_sz (fd));
	}
	if (count > 0) {
		memcpy (_io_malloc_buf (fd) + _io_malloc_off (fd), buf, count);
		_io_malloc_set_off (fd, _io_malloc_off (fd) + count);
		return count;
	}
	return -1;
}