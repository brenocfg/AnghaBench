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
typedef  int /*<<< orphan*/  umode_t ;

/* Variables and functions */
 unsigned char fs_ftype_to_dtype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs_umode_to_ftype (int /*<<< orphan*/ ) ; 

unsigned char fs_umode_to_dtype(umode_t mode)
{
	return fs_ftype_to_dtype(fs_umode_to_ftype(mode));
}