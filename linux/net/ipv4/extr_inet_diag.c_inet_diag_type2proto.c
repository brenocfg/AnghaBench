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
#define  DCCPDIAG_GETSOCK 129 
 int IPPROTO_DCCP ; 
 int IPPROTO_TCP ; 
#define  TCPDIAG_GETSOCK 128 

__attribute__((used)) static int inet_diag_type2proto(int type)
{
	switch (type) {
	case TCPDIAG_GETSOCK:
		return IPPROTO_TCP;
	case DCCPDIAG_GETSOCK:
		return IPPROTO_DCCP;
	default:
		return 0;
	}
}