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
#define  CON_FLAG_BACKOFF 132 
#define  CON_FLAG_KEEPALIVE_PENDING 131 
#define  CON_FLAG_LOSSYTX 130 
#define  CON_FLAG_SOCK_CLOSED 129 
#define  CON_FLAG_WRITE_PENDING 128 

__attribute__((used)) static bool con_flag_valid(unsigned long con_flag)
{
	switch (con_flag) {
	case CON_FLAG_LOSSYTX:
	case CON_FLAG_KEEPALIVE_PENDING:
	case CON_FLAG_WRITE_PENDING:
	case CON_FLAG_SOCK_CLOSED:
	case CON_FLAG_BACKOFF:
		return true;
	default:
		return false;
	}
}