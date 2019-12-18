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
typedef  int /*<<< orphan*/  uint8_t ;
struct ud {int inp_buf_index; int inp_ctr; int /*<<< orphan*/  const* inp_buf; int /*<<< orphan*/  const* inp_sess; } ;

/* Variables and functions */

extern const uint8_t* 
ud_insn_ptr(const struct ud* u) 
{
  return (u->inp_buf == NULL) ? 
            u->inp_sess : u->inp_buf + (u->inp_buf_index - u->inp_ctr);
}