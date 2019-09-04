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
typedef  int zip_uint64_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  putc (int,int /*<<< orphan*/ *) ; 

void
_zip_write8(zip_uint64_t i, FILE *fp)
{
    putc(i&0xff, fp);
    putc((i>>8)&0xff, fp);
    putc((i>>16)&0xff, fp);
    putc((i>>24)&0xff, fp);
    putc((i>>32)&0xff, fp);
    putc((i>>40)&0xff, fp);
    putc((i>>48)&0xff, fp);
    putc((i>>56)&0xff, fp);
    
    return;
}