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
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  RLineCompletion ;
typedef  TYPE_1__ RFlagItem ;

/* Variables and functions */
 int /*<<< orphan*/  r_line_completion_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool add_argv(RFlagItem *fi, void *user) {
	RLineCompletion *completion = user;
	r_line_completion_push (completion, fi->name);
	return true;
}