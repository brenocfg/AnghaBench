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
typedef  int ut64 ;
struct TYPE_3__ {int (* disasm ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  user; } ;
typedef  TYPE_1__ RPrint ;

/* Variables and functions */
 int R_MAX (int,int) ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int r_print_format_disasm(const RPrint* p, ut64 seeki, int size) {
	ut64 prevseeki = seeki;

	if (!p->disasm || !p->user) {
		return 0;
	}

	size = R_MAX (1, size);

	while (size-- > 0) {
		seeki += p->disasm (p->user, seeki);
	}

	return seeki - prevseeki;
}