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
typedef  int uint8_t ;
struct ud {int inp_end; int* inp_buf; scalar_t__ inp_buf_index; scalar_t__ inp_buf_size; int inp_curr; int inp_peek; int (* inp_hook ) (struct ud*) ;int* inp_sess; int /*<<< orphan*/  inp_ctr; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDERR (struct ud*,char*) ; 
 int UD_EOI ; 
 int stub1 (struct ud*) ; 

__attribute__((used)) static uint8_t
inp_next(struct ud *u)
{
  if (u->inp_end == 0) {
    if (u->inp_buf != NULL) {
      if (u->inp_buf_index < u->inp_buf_size) {
        u->inp_ctr++;
        return (u->inp_curr = u->inp_buf[u->inp_buf_index++]);
      }
    } else {
      int c = u->inp_peek;
      if (c != UD_EOI || (c = u->inp_hook(u)) != UD_EOI) {
        u->inp_peek = UD_EOI;
        u->inp_curr = c;
        u->inp_sess[u->inp_ctr++] = u->inp_curr;
        return u->inp_curr;
      }
    }
  }
  u->inp_end = 1;
  UDERR(u, "byte expected, eoi received\n");
  return 0;
}