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
typedef  int /*<<< orphan*/  png_size_t ;
struct TYPE_4__ {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  PNG_HAVE_IEND ; 
 int /*<<< orphan*/  PNG_IEND ; 
 int /*<<< orphan*/  png_IEND ; 
 int /*<<< orphan*/  png_bytep_NULL ; 
 int /*<<< orphan*/  png_debug (int,char*) ; 
 int /*<<< orphan*/  png_write_chunk (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void /* PRIVATE */
png_write_IEND(png_structp png_ptr)
{
#ifdef PNG_USE_LOCAL_ARRAYS
   PNG_IEND;
#endif
   png_debug(1, "in png_write_IEND\n");
   png_write_chunk(png_ptr, png_IEND, png_bytep_NULL,
     (png_size_t)0);
   png_ptr->mode |= PNG_HAVE_IEND;
}