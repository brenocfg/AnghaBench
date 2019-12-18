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
typedef  int uint8_t ;
typedef  int uint16_t ;
struct serializer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  s_w8 (struct serializer*,int) ; 

__attribute__((used)) static inline void s_wl16(struct serializer *s, uint16_t u16)
{
	s_w8(s, (uint8_t)u16);
	s_w8(s, u16 >> 8);
}