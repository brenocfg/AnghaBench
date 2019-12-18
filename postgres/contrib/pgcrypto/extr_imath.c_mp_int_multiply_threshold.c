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
typedef  int /*<<< orphan*/  mp_word ;
typedef  int mp_size ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int multiply_threshold ; 

void
mp_int_multiply_threshold(mp_size thresh)
{
	assert(thresh >= sizeof(mp_word));
	multiply_threshold = thresh;
}