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
struct pdo_pgsql_lob_self {int /*<<< orphan*/  lfd; int /*<<< orphan*/  conn; } ;
struct TYPE_3__ {scalar_t__ abstract; } ;
typedef  TYPE_1__ php_stream ;

/* Variables and functions */
 size_t lo_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t) ; 

__attribute__((used)) static size_t pgsql_lob_write(php_stream *stream, const char *buf, size_t count)
{
	struct pdo_pgsql_lob_self *self = (struct pdo_pgsql_lob_self*)stream->abstract;
	return lo_write(self->conn, self->lfd, (char*)buf, count);
}