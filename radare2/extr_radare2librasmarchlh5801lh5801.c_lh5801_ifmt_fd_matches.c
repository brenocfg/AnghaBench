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
typedef  enum lh5801_insn_format { ____Placeholder_lh5801_insn_format } lh5801_insn_format ;

/* Variables and functions */
 int LH5801_IFMT_FD_MASK ; 
#define  LH5801_IFMT_FD_MOD 130 
#define  LH5801_IFMT_FD_NO 129 
#define  LH5801_IFMT_FD_YES 128 

__attribute__((used)) static bool lh5801_ifmt_fd_matches(enum lh5801_insn_format fmt, int fd) {
	switch (fmt & LH5801_IFMT_FD_MASK) {
	case LH5801_IFMT_FD_NO: 	return !fd;
	case LH5801_IFMT_FD_YES:	return fd;
	case LH5801_IFMT_FD_MOD:	return true;
	default:			return false;
	}
}