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
 scalar_t__ char_class (char const,unsigned int const) ; 

__attribute__((used)) static inline bool
char_inc_exc(const char c, const unsigned int inclusive, const unsigned int exclusive)
{
    return char_class(c, inclusive) && !char_class(c, exclusive);
}