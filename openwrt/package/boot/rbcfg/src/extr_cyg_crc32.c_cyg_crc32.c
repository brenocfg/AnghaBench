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
typedef  int /*<<< orphan*/  cyg_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  cyg_crc32_accumulate (int /*<<< orphan*/ ,unsigned char*,int) ; 

cyg_uint32
cyg_crc32(unsigned char *s, int len)
{
  return (cyg_crc32_accumulate(0,s,len));
}