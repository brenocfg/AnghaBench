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
typedef  int /*<<< orphan*/  mrb_bool ;
struct TYPE_3__ {char* cmd1; char* cmd2; char* short_msg; } ;
typedef  TYPE_1__ help_msg ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* help_msg_list ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static mrb_bool
show_short_help(void)
{
  help_msg *p;

  printf("Commands\n");

  for (p = help_msg_list; p->cmd1 != NULL; p++) {
    if (p->cmd2 == NULL) {
      printf("  %s -- %s\n", p->cmd1, p->short_msg);
    }
    else {
      printf("  %s %s -- %s\n", p->cmd1, p->cmd2, p->short_msg);
    }
  }
  return TRUE;
}