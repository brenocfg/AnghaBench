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
 int /*<<< orphan*/  BUG () ; 
 int DLM_LOCK_CW ; 
 int DLM_LOCK_EX ; 
 int DLM_LOCK_NL ; 
 int DLM_LOCK_PR ; 
#define  LM_ST_DEFERRED 131 
#define  LM_ST_EXCLUSIVE 130 
#define  LM_ST_SHARED 129 
#define  LM_ST_UNLOCKED 128 
 int /*<<< orphan*/  pr_err (char*,unsigned int const) ; 

__attribute__((used)) static int make_mode(const unsigned int lmstate)
{
	switch (lmstate) {
	case LM_ST_UNLOCKED:
		return DLM_LOCK_NL;
	case LM_ST_EXCLUSIVE:
		return DLM_LOCK_EX;
	case LM_ST_DEFERRED:
		return DLM_LOCK_CW;
	case LM_ST_SHARED:
		return DLM_LOCK_PR;
	}
	pr_err("unknown LM state %d\n", lmstate);
	BUG();
	return -1;
}