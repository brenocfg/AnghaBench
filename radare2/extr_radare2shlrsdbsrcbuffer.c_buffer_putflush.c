#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut32 ;
struct TYPE_4__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  op; } ;
typedef  TYPE_1__ buffer ;

/* Variables and functions */
 int allwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_flush (TYPE_1__*) ; 

int buffer_putflush(buffer *s, const char *buf, ut32 len) {
	if (!buffer_flush (s)) {
		return 0;
	}
	return allwrite (s->op, s->fd, buf, len);
}