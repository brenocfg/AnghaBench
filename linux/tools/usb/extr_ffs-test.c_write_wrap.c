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
struct thread {int /*<<< orphan*/  fd; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,void const*,size_t) ; 

__attribute__((used)) static ssize_t write_wrap(struct thread *t, const void *buf, size_t nbytes)
{
	return write(t->fd, buf, nbytes);
}