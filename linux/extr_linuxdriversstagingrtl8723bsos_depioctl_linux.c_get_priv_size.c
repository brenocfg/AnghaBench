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
typedef  int __u16 ;

/* Variables and functions */
 int IW_PRIV_SIZE_MASK ; 
 int IW_PRIV_TYPE_MASK ; 
 int* iw_priv_type_size ; 

__attribute__((used)) static int get_priv_size(__u16 args)
{
	int num = args & IW_PRIV_SIZE_MASK;
	int type = (args & IW_PRIV_TYPE_MASK) >> 12;

	return num * iw_priv_type_size[type];
}