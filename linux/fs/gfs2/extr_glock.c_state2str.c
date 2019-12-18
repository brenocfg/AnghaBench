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
#define  LM_ST_DEFERRED 131 
#define  LM_ST_EXCLUSIVE 130 
#define  LM_ST_SHARED 129 
#define  LM_ST_UNLOCKED 128 

__attribute__((used)) static const char *state2str(unsigned state)
{
	switch(state) {
	case LM_ST_UNLOCKED:
		return "UN";
	case LM_ST_SHARED:
		return "SH";
	case LM_ST_DEFERRED:
		return "DF";
	case LM_ST_EXCLUSIVE:
		return "EX";
	}
	return "??";
}