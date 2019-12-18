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
struct thread {scalar_t__ fd; int /*<<< orphan*/  filename; int /*<<< orphan*/  buf; int /*<<< orphan*/  buf_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  die_on (int,char*,...) ; 
 int /*<<< orphan*/  malloc (int /*<<< orphan*/ ) ; 
 scalar_t__ open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_thread(struct thread *t)
{
	t->buf = malloc(t->buf_size);
	die_on(!t->buf, "malloc");

	t->fd = open(t->filename, O_RDWR);
	die_on(t->fd < 0, "%s", t->filename);
}