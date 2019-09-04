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
 int NFS4_READW_LT ; 
 int NFS4_READ_LT ; 
 int RD_STATE ; 
 int WR_STATE ; 

__attribute__((used)) static inline int
setlkflg (int type)
{
	return (type == NFS4_READW_LT || type == NFS4_READ_LT) ?
		RD_STATE : WR_STATE;
}