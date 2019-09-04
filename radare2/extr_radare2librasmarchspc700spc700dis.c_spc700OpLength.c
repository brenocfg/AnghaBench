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
#define  SPC_ARG16 131 
#define  SPC_ARG8_1 130 
#define  SPC_ARG8_2 129 
#define  SPC_OP 128 

__attribute__((used)) static int spc700OpLength(int spcoptype){
	switch(spcoptype) {
	case SPC_OP:
		return 1;
	case SPC_ARG8_1:
		return 2;
	case SPC_ARG8_2:
	case SPC_ARG16:
		return 3;
	}
	return 0;
}