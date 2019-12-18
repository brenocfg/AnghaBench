#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* png_structp ;
typedef  int /*<<< orphan*/  png_bytep ;
struct TYPE_4__ {scalar_t__ pass; int /*<<< orphan*/  row_number; int /*<<< orphan*/  (* row_fn ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void /* PRIVATE */
png_push_have_row(png_structp png_ptr, png_bytep row)
{
   if (png_ptr->row_fn != NULL)
      (*(png_ptr->row_fn))(png_ptr, row, png_ptr->row_number,
         (int)png_ptr->pass);
}