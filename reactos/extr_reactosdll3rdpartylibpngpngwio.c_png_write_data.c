#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* png_structrp ;
typedef  int /*<<< orphan*/  png_const_bytep ;
struct TYPE_5__ {int /*<<< orphan*/  (* write_data_fn ) (TYPE_1__*,int /*<<< orphan*/ ,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  png_bytep ; 
 int /*<<< orphan*/  png_constcast (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_error (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,size_t) ; 

void /* PRIVATE */
png_write_data(png_structrp png_ptr, png_const_bytep data, size_t length)
{
   /* NOTE: write_data_fn must not change the buffer! */
   if (png_ptr->write_data_fn != NULL )
      (*(png_ptr->write_data_fn))(png_ptr, png_constcast(png_bytep,data),
          length);

   else
      png_error(png_ptr, "Call to NULL write function");
}