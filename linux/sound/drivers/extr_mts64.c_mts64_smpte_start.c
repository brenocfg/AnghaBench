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
struct parport {int dummy; } ;

/* Variables and functions */
#define  MTS64_CMD_SMPTE_FPS_24 132 
#define  MTS64_CMD_SMPTE_FPS_25 131 
#define  MTS64_CMD_SMPTE_FPS_2997 130 
#define  MTS64_CMD_SMPTE_FPS_30 129 
#define  MTS64_CMD_SMPTE_FPS_30D 128 
 size_t MTS64_CMD_SMPTE_SET_FPS ; 
 size_t MTS64_CMD_SMPTE_SET_TIME ; 
 int /*<<< orphan*/  mts64_write_command (struct parport*,size_t) ; 

__attribute__((used)) static void mts64_smpte_start(struct parport *p,
			      u8 hours, u8 minutes,
			      u8 seconds, u8 frames,
			      u8 idx)
{
	static u8 fps[5] = { MTS64_CMD_SMPTE_FPS_24, 
			     MTS64_CMD_SMPTE_FPS_25,
			     MTS64_CMD_SMPTE_FPS_2997, 
			     MTS64_CMD_SMPTE_FPS_30D,
			     MTS64_CMD_SMPTE_FPS_30    };

	mts64_write_command(p, MTS64_CMD_SMPTE_SET_TIME);
	mts64_write_command(p, frames);
	mts64_write_command(p, seconds);
	mts64_write_command(p, minutes);
	mts64_write_command(p, hours);

	mts64_write_command(p, MTS64_CMD_SMPTE_SET_FPS);
	mts64_write_command(p, fps[idx]);
}