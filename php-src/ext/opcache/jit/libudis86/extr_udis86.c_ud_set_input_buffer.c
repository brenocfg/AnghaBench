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
struct ud {size_t inp_buf_size; scalar_t__ inp_buf_index; int /*<<< orphan*/  const* inp_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ud_inp_init (struct ud*) ; 

void 
ud_set_input_buffer(register struct ud* u, const uint8_t* buf, size_t len)
{
  ud_inp_init(u);
  u->inp_buf = buf;
  u->inp_buf_size = len;
  u->inp_buf_index = 0;
}