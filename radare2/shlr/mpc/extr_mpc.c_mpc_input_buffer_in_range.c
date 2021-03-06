#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {long pos; } ;
struct TYPE_7__ {TYPE_2__* marks; int /*<<< orphan*/  buffer; TYPE_1__ state; } ;
typedef  TYPE_3__ mpc_input_t ;
struct TYPE_6__ {scalar_t__ pos; } ;

/* Variables and functions */
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mpc_input_buffer_in_range(mpc_input_t *i) {
  return i->state.pos < (long)(strlen(i->buffer) + i->marks[0].pos);
}