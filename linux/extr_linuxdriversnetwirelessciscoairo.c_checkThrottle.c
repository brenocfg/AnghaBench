#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ authType; scalar_t__* rates; } ;
struct airo_info {TYPE_1__ config; } ;

/* Variables and functions */
 scalar_t__ AUTH_OPEN ; 
 scalar_t__ maxencrypt ; 

__attribute__((used)) static inline void checkThrottle(struct airo_info *ai)
{
	int i;
/* Old hardware had a limit on encryption speed */
	if (ai->config.authType != AUTH_OPEN && maxencrypt) {
		for(i=0; i<8; i++) {
			if (ai->config.rates[i] > maxencrypt) {
				ai->config.rates[i] = 0;
			}
		}
	}
}