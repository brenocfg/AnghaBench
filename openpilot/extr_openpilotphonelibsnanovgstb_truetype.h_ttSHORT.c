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
typedef  int stbtt_uint8 ;
typedef  int const stbtt_int16 ;

/* Variables and functions */

__attribute__((used)) static stbtt_int16 ttSHORT(const stbtt_uint8 *p)   { return p[0]*256 + p[1]; }