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
struct TYPE_3__ {int p; int /*<<< orphan*/  x; int /*<<< orphan*/  fd; int /*<<< orphan*/  op; } ;
typedef  TYPE_1__ buffer ;

/* Variables and functions */
 int allwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int buffer_flush(buffer *s) {
	int p = s->p;
	if (!p) {
		return 1;
	}
	s->p = 0;
	return allwrite (s->op, s->fd, s->x, p);
}