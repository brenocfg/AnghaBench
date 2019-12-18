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
struct jsonsl_state_st {size_t pos_begin; } ;
struct TYPE_3__ {size_t min_available; char const* buffer; } ;
typedef  TYPE_1__ JSN_DATA ;

/* Variables and functions */

__attribute__((used)) static const char* get_state_buffer(JSN_DATA *ctx, struct jsonsl_state_st *state)
{
  size_t offset = state->pos_begin - ctx->min_available;
  return ctx->buffer + offset;
}