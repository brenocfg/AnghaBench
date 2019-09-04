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
typedef  int zend_ulong ;

/* Variables and functions */
 int minAND (int,int,int,int) ; 

zend_ulong minXOR(zend_ulong a, zend_ulong b, zend_ulong c, zend_ulong d)
{
	return minAND(a, b, ~d, ~c) | minAND(~b, ~a, c, d);
}