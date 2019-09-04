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
struct hecubafb_par {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dio_addr ; 
 int /*<<< orphan*/  outb (unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void n411_set_data(struct hecubafb_par *par, unsigned char value)
{
	outb(value, dio_addr);
}