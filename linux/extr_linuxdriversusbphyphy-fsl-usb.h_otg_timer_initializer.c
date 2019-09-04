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
struct fsl_otg_timer {void (* function ) (unsigned long) ;unsigned long expires; unsigned long data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct fsl_otg_timer* kmalloc (int,int /*<<< orphan*/ ) ; 

inline struct fsl_otg_timer *otg_timer_initializer
(void (*function)(unsigned long), unsigned long expires, unsigned long data)
{
	struct fsl_otg_timer *timer;

	timer = kmalloc(sizeof(struct fsl_otg_timer), GFP_KERNEL);
	if (!timer)
		return NULL;
	timer->function = function;
	timer->expires = expires;
	timer->data = data;
	return timer;
}