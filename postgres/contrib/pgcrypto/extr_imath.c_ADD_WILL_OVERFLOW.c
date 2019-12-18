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
typedef  scalar_t__ mp_word ;

/* Variables and functions */
 scalar_t__ MP_WORD_MAX ; 

__attribute__((used)) static inline bool
ADD_WILL_OVERFLOW(mp_word W, mp_word V)
{
	return ((MP_WORD_MAX - V) < W);
}