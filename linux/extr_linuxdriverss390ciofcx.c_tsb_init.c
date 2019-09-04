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
struct tsb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct tsb*,int /*<<< orphan*/ ,int) ; 

void tsb_init(struct tsb *tsb)
{
	memset(tsb, 0, sizeof(*tsb));
}