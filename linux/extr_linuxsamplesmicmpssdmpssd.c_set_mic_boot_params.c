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
struct mic_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_cmdline (struct mic_info*) ; 
 int /*<<< orphan*/  set_log_buf_info (struct mic_info*) ; 

__attribute__((used)) static void
set_mic_boot_params(struct mic_info *mic)
{
	set_log_buf_info(mic);
	set_cmdline(mic);
}