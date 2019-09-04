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
struct mbochs_mode {int dummy; } ;

/* Variables and functions */
 scalar_t__ memcmp (struct mbochs_mode*,struct mbochs_mode*,int) ; 

__attribute__((used)) static bool mbochs_modes_equal(struct mbochs_mode *mode1,
			       struct mbochs_mode *mode2)
{
	return memcmp(mode1, mode2, sizeof(struct mbochs_mode)) == 0;
}