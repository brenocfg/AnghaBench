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
struct snd_ice1712 {struct qtet_spec* spec; } ;
struct qtet_spec {unsigned int cpld; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_CPLD_CSN ; 
 int /*<<< orphan*/  reg_write (struct snd_ice1712*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void set_cpld(struct snd_ice1712 *ice, unsigned int val)
{
	struct qtet_spec *spec = ice->spec;
	reg_write(ice, GPIO_CPLD_CSN, val);
	spec->cpld = val;
}