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
 scalar_t__ isdigit (char const) ; 
 scalar_t__ isspace (char const) ; 

__attribute__((used)) static inline int isoperatorterm_word(const char s) {
    if(isspace(s) || s == '(' || s == '$' || s == '!' || s == '-' || s == '+' || isdigit(s) || !s)
        return 1;

    return 0;
}