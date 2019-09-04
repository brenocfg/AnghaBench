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
typedef  scalar_t__ uint32 ;
struct cdb_make {int /*<<< orphan*/  fp; } ;

/* Variables and functions */
 scalar_t__ php_stream_write (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static int cdb_make_write(struct cdb_make *c, char *buf, uint32 sz) {
	return php_stream_write(c->fp, buf, sz) == sz ? 0 : -1;
}