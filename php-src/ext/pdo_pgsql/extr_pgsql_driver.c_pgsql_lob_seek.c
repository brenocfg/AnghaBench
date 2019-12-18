#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ zend_off_t ;
struct pdo_pgsql_lob_self {int /*<<< orphan*/  lfd; int /*<<< orphan*/  conn; } ;
struct TYPE_3__ {scalar_t__ abstract; } ;
typedef  TYPE_1__ php_stream ;

/* Variables and functions */
 scalar_t__ lo_lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ lo_lseek64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int pgsql_lob_seek(php_stream *stream, zend_off_t offset, int whence,
		zend_off_t *newoffset)
{
	struct pdo_pgsql_lob_self *self = (struct pdo_pgsql_lob_self*)stream->abstract;
#if HAVE_PG_LO64 && ZEND_ENABLE_ZVAL_LONG64
	zend_off_t pos = lo_lseek64(self->conn, self->lfd, offset, whence);
#else
	zend_off_t pos = lo_lseek(self->conn, self->lfd, offset, whence);
#endif
	*newoffset = pos;
	return pos >= 0 ? 0 : -1;
}