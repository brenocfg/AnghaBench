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
struct tun_struct {int /*<<< orphan*/  numdisabled; int /*<<< orphan*/  disabled; } ;
struct tun_file {int /*<<< orphan*/  next; struct tun_struct* detached; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tun_disable_queue(struct tun_struct *tun, struct tun_file *tfile)
{
	tfile->detached = tun;
	list_add_tail(&tfile->next, &tun->disabled);
	++tun->numdisabled;
}