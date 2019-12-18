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
typedef  int /*<<< orphan*/  png_uint_32 ;
typedef  TYPE_1__* png_structp ;
struct TYPE_3__ {int /*<<< orphan*/  skip_length; int /*<<< orphan*/  process_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  PNG_SKIP_MODE ; 

void /* PRIVATE */
png_push_crc_skip(png_structp png_ptr, png_uint_32 skip)
{
   png_ptr->process_mode = PNG_SKIP_MODE;
   png_ptr->skip_length = skip;
}