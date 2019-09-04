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
struct ud {int /*<<< orphan*/ * inp_file; int /*<<< orphan*/  inp_peek; scalar_t__ inp_end; scalar_t__ inp_ctr; scalar_t__ inp_curr; scalar_t__ inp_buf_index; scalar_t__ inp_buf_size; int /*<<< orphan*/ * inp_buf; int /*<<< orphan*/ * inp_hook; } ;

/* Variables and functions */
 int /*<<< orphan*/  UD_EOI ; 
 int /*<<< orphan*/  UD_NON_STANDALONE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ud_inp_init(struct ud *u)
{
  u->inp_hook      = NULL;
  u->inp_buf       = NULL;
  u->inp_buf_size  = 0;
  u->inp_buf_index = 0;
  u->inp_curr      = 0;
  u->inp_ctr       = 0;
  u->inp_end       = 0;
  u->inp_peek      = UD_EOI;
  UD_NON_STANDALONE(u->inp_file = NULL);
}