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
struct dasd_device {int dummy; } ;
typedef  int __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  dasd_path_nohpf (struct dasd_device*,int) ; 

__attribute__((used)) static inline void dasd_path_add_nohpfpm(struct dasd_device *device, __u8 pm)
{
	int chp;

	for (chp = 0; chp < 8; chp++)
		if (pm & (0x80 >> chp))
			dasd_path_nohpf(device, chp);
}