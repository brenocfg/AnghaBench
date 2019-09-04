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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_LOCK_CW ; 
 int /*<<< orphan*/  DLM_LOCK_EX ; 
 int /*<<< orphan*/  DLM_LOCK_NL ; 
 int /*<<< orphan*/  DLM_LOCK_PR ; 
#define  LM_ST_DEFERRED 130 
#define  LM_ST_EXCLUSIVE 129 
#define  LM_ST_SHARED 128 

__attribute__((used)) static inline u8 glock_trace_state(unsigned int state)
{
	switch(state) {
	case LM_ST_SHARED:
		return DLM_LOCK_PR;
	case LM_ST_DEFERRED:
		return DLM_LOCK_CW;
	case LM_ST_EXCLUSIVE:
		return DLM_LOCK_EX;
	}
	return DLM_LOCK_NL;
}