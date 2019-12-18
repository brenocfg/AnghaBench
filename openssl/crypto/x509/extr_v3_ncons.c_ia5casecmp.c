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
 int /*<<< orphan*/  SIZE_MAX ; 
 int ia5ncasecmp (char const*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ia5casecmp(const char *s1, const char *s2)
{
    return ia5ncasecmp(s1, s2, SIZE_MAX);
}