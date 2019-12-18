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
typedef  size_t u8 ;
struct smp_chan {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 size_t JUST_CFM ; 
 int /*<<< orphan*/  SMP_FLAG_SC ; 
 size_t SMP_IO_KEYBOARD_DISPLAY ; 
 size_t** gen_method ; 
 size_t** sc_method ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u8 get_auth_method(struct smp_chan *smp, u8 local_io, u8 remote_io)
{
	/* If either side has unknown io_caps, use JUST_CFM (which gets
	 * converted later to JUST_WORKS if we're initiators.
	 */
	if (local_io > SMP_IO_KEYBOARD_DISPLAY ||
	    remote_io > SMP_IO_KEYBOARD_DISPLAY)
		return JUST_CFM;

	if (test_bit(SMP_FLAG_SC, &smp->flags))
		return sc_method[remote_io][local_io];

	return gen_method[remote_io][local_io];
}