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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ DXGI_FORMAT_B5G5R5A1_UNORM ; 
 scalar_t__ DXGI_FORMAT_B5G6R5_UNORM ; 

__attribute__((used)) static inline bool is_16bit_format(uint32_t format)
{
	return format == DXGI_FORMAT_B5G5R5A1_UNORM ||
	       format == DXGI_FORMAT_B5G6R5_UNORM;
}