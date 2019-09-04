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
typedef  int /*<<< orphan*/  voidpf ;

/* Variables and functions */
 int /*<<< orphan*/  png_const_structrp ; 
 int /*<<< orphan*/  png_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_voidcast (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void /* PRIVATE */
png_zfree(voidpf png_ptr, voidpf ptr)
{
   png_free(png_voidcast(png_const_structrp,png_ptr), ptr);
}