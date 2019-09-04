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
struct ud {int /*<<< orphan*/ * inp_file; int /*<<< orphan*/  inp_hook; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  inp_file_hook ; 
 int /*<<< orphan*/  ud_inp_init (struct ud*) ; 

void 
ud_set_input_file(register struct ud* u, FILE* f)
{
  ud_inp_init(u);
  u->inp_hook = inp_file_hook;
  u->inp_file = f;
}