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
struct ak4117 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AK4117_REG_RCS1 ; 
 int external_rate (unsigned char) ; 
 unsigned char reg_read (struct ak4117*,int /*<<< orphan*/ ) ; 

int snd_ak4117_external_rate(struct ak4117 *ak4117)
{
	unsigned char rcs1;

	rcs1 = reg_read(ak4117, AK4117_REG_RCS1);
	return external_rate(rcs1);
}