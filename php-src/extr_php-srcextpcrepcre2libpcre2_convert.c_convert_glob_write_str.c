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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {scalar_t__ output_size; int /*<<< orphan*/ * output; int /*<<< orphan*/ * output_end; int /*<<< orphan*/ * out_str; } ;
typedef  TYPE_1__ pcre2_output_context ;
typedef  int /*<<< orphan*/  PCRE2_UCHAR ;
typedef  int /*<<< orphan*/ * PCRE2_SPTR ;
typedef  scalar_t__ PCRE2_SIZE ;

/* Variables and functions */

__attribute__((used)) static void
convert_glob_write_str(pcre2_output_context *out, PCRE2_SIZE length)
{
uint8_t *out_str = out->out_str;
PCRE2_UCHAR *output = out->output;
PCRE2_SPTR output_end = out->output_end;
PCRE2_SIZE output_size = out->output_size;

do
  {
  output_size++;

  if (output < output_end)
    *output++ = *out_str++;
  }
while (--length != 0);

out->output = output;
out->output_size = output_size;
}