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
typedef  int pcre_uint16 ;

/* Variables and functions */

__attribute__((used)) static pcre_uint16
swap_uint16(pcre_uint16 value)
{
return (value >> 8) | (value << 8);
}