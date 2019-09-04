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
typedef  int /*<<< orphan*/  u32 ;
struct usba_udc {int /*<<< orphan*/  int_enb_cache; } ;

/* Variables and functions */

__attribute__((used)) static inline u32 usba_int_enb_get(struct usba_udc *udc)
{
	return udc->int_enb_cache;
}