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
struct c67x00_sie {int mode; } ;

/* Variables and functions */
#define  C67X00_SIE_HOST 128 
 int /*<<< orphan*/  c67x00_hcd_remove (struct c67x00_sie*) ; 

__attribute__((used)) static void c67x00_remove_sie(struct c67x00_sie *sie)
{
	switch (sie->mode) {
	case C67X00_SIE_HOST:
		c67x00_hcd_remove(sie);
		break;

	default:
		break;
	}
}