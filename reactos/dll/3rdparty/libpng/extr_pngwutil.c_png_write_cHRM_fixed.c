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
struct TYPE_3__ {int /*<<< orphan*/  bluey; int /*<<< orphan*/  bluex; int /*<<< orphan*/  greeny; int /*<<< orphan*/  greenx; int /*<<< orphan*/  redy; int /*<<< orphan*/  redx; int /*<<< orphan*/  whitey; int /*<<< orphan*/  whitex; } ;
typedef  TYPE_1__ png_xy ;
typedef  int /*<<< orphan*/  png_structrp ;
typedef  int /*<<< orphan*/  png_byte ;

/* Variables and functions */
 int /*<<< orphan*/  png_cHRM ; 
 int /*<<< orphan*/  png_debug (int,char*) ; 
 int /*<<< orphan*/  png_save_int_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_write_complete_chunk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

void /* PRIVATE */
png_write_cHRM_fixed(png_structrp png_ptr, const png_xy *xy)
{
   png_byte buf[32];

   png_debug(1, "in png_write_cHRM");

   /* Each value is saved in 1/100,000ths */
   png_save_int_32(buf,      xy->whitex);
   png_save_int_32(buf +  4, xy->whitey);

   png_save_int_32(buf +  8, xy->redx);
   png_save_int_32(buf + 12, xy->redy);

   png_save_int_32(buf + 16, xy->greenx);
   png_save_int_32(buf + 20, xy->greeny);

   png_save_int_32(buf + 24, xy->bluex);
   png_save_int_32(buf + 28, xy->bluey);

   png_write_complete_chunk(png_ptr, png_cHRM, buf, 32);
}