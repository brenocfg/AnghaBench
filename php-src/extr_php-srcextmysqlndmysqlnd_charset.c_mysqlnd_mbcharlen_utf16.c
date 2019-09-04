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
typedef  int uint32_t ;

/* Variables and functions */
 scalar_t__ UTF16_HIGH_HEAD (unsigned int const) ; 

__attribute__((used)) static uint32_t mysqlnd_mbcharlen_utf16(const unsigned int utf16)
{
  return UTF16_HIGH_HEAD(utf16) ? 4 : 2;
}