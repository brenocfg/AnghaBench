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
struct es1968 {int dummy; } ;

/* Variables and functions */
 int __apu_get_register (struct es1968*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __apu_set_register (struct es1968*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void snd_es1968_trigger_apu(struct es1968 *esm, int apu, int mode)
{
	/* set the APU mode */
	__apu_set_register(esm, apu, 0,
			   (__apu_get_register(esm, apu, 0) & 0xff0f) |
			   (mode << 4));
}