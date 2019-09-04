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

/* Variables and functions */
#define  TC_ACT_QUEUED 131 
#define  TC_ACT_SHOT 130 
#define  TC_ACT_STOLEN 129 
#define  TC_ACT_TRAP 128 

__attribute__((used)) static bool tcf_mirred_can_reinsert(int action)
{
	switch (action) {
	case TC_ACT_SHOT:
	case TC_ACT_STOLEN:
	case TC_ACT_QUEUED:
	case TC_ACT_TRAP:
		return true;
	}
	return false;
}