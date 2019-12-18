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
struct sigma_action {int instr; } ;

/* Variables and functions */
 size_t ALIGN (size_t,int) ; 
#define  SIGMA_ACTION_WRITESAFELOAD 130 
#define  SIGMA_ACTION_WRITESINGLE 129 
#define  SIGMA_ACTION_WRITEXBYTES 128 
 size_t sigma_action_len (struct sigma_action*) ; 

__attribute__((used)) static size_t sigma_action_size(struct sigma_action *sa)
{
	size_t payload = 0;

	switch (sa->instr) {
	case SIGMA_ACTION_WRITEXBYTES:
	case SIGMA_ACTION_WRITESINGLE:
	case SIGMA_ACTION_WRITESAFELOAD:
		payload = sigma_action_len(sa);
		break;
	default:
		break;
	}

	payload = ALIGN(payload, 2);

	return payload + sizeof(struct sigma_action);
}