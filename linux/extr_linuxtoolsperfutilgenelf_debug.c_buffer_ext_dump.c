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
struct buffer_ext {size_t cur_pos; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static void
buffer_ext_dump(struct buffer_ext *be, const char *msg)
{
	size_t i;
	warnx("DUMP for %s", msg);
	for (i = 0 ; i < be->cur_pos; i++)
		warnx("%4zu 0x%02x", i, (((char *)be->data)[i]) & 0xff);
}