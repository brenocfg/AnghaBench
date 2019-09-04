#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  scalar_t__ ut64 ;
typedef  scalar_t__ ut32 ;
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ RIODesc ;
typedef  int /*<<< orphan*/  RIO ;

/* Variables and functions */
 int /*<<< orphan*/  R_MIN (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  _io_malloc_buf (TYPE_1__*) ; 
 scalar_t__ _io_malloc_off (TYPE_1__*) ; 
 int /*<<< orphan*/  _io_malloc_set_buf (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _io_malloc_set_sz (TYPE_1__*,scalar_t__) ; 
 scalar_t__ _io_malloc_sz (TYPE_1__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static bool __resize(RIO *io, RIODesc *fd, ut64 count) {
	ut8 * new_buf = NULL;
	if (!fd || !fd->data || count == 0) {
		return false;
	}
	ut32 mallocsz = _io_malloc_sz (fd);
	if (_io_malloc_off (fd) > mallocsz) {
		return false;
	}
	new_buf = malloc (count);
	if (!new_buf) {
		return -1;
	}
	memcpy (new_buf, _io_malloc_buf (fd), R_MIN (count, mallocsz));
	if (count > mallocsz) {
		memset (new_buf + mallocsz, 0, count - mallocsz);
	}
	free (_io_malloc_buf (fd));
	_io_malloc_set_buf (fd, new_buf);
	_io_malloc_set_sz (fd, count);
	return true;
}