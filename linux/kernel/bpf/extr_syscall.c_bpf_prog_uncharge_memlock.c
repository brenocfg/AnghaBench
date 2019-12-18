#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct user_struct {int dummy; } ;
struct bpf_prog {int /*<<< orphan*/  pages; TYPE_1__* aux; } ;
struct TYPE_2__ {struct user_struct* user; } ;

/* Variables and functions */
 int /*<<< orphan*/  __bpf_prog_uncharge (struct user_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_uid (struct user_struct*) ; 

__attribute__((used)) static void bpf_prog_uncharge_memlock(struct bpf_prog *prog)
{
	struct user_struct *user = prog->aux->user;

	__bpf_prog_uncharge(user, prog->pages);
	free_uid(user);
}