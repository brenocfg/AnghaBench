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
struct bpf_prog {TYPE_1__* aux; int /*<<< orphan*/  pages; } ;
struct TYPE_2__ {struct user_struct* user; } ;

/* Variables and functions */
 int __bpf_prog_charge (struct user_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_uid (struct user_struct*) ; 
 struct user_struct* get_current_user () ; 

__attribute__((used)) static int bpf_prog_charge_memlock(struct bpf_prog *prog)
{
	struct user_struct *user = get_current_user();
	int ret;

	ret = __bpf_prog_charge(user, prog->pages);
	if (ret) {
		free_uid(user);
		return ret;
	}

	prog->aux->user = user;
	return 0;
}