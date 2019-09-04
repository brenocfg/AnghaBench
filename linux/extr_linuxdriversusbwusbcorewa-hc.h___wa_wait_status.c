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
typedef  int u32 ;
struct wahc {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int __wa_get_status (struct wahc*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static inline s32 __wa_wait_status(struct wahc *wa, u32 mask, u32 value)
{
	s32 result;
	unsigned loops = 10;
	do {
		msleep(50);
		result = __wa_get_status(wa);
		if ((result & mask) == value)
			break;
		if (loops-- == 0) {
			result = -ETIMEDOUT;
			break;
		}
	} while (result >= 0);
	return result;
}