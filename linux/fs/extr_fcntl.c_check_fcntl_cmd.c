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
#define  F_DUPFD 132 
#define  F_DUPFD_CLOEXEC 131 
#define  F_GETFD 130 
#define  F_GETFL 129 
#define  F_SETFD 128 

__attribute__((used)) static int check_fcntl_cmd(unsigned cmd)
{
	switch (cmd) {
	case F_DUPFD:
	case F_DUPFD_CLOEXEC:
	case F_GETFD:
	case F_SETFD:
	case F_GETFL:
		return 1;
	}
	return 0;
}