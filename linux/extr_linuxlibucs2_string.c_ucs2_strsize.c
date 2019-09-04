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
typedef  int /*<<< orphan*/  ucs2_char_t ;

/* Variables and functions */
 int ucs2_strnlen (int /*<<< orphan*/  const*,unsigned long) ; 

unsigned long
ucs2_strsize(const ucs2_char_t *data, unsigned long maxlength)
{
        return ucs2_strnlen(data, maxlength/sizeof(ucs2_char_t)) * sizeof(ucs2_char_t);
}