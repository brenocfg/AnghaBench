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
 int MPMIN (int,int) ; 
 int prefix_len (char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strncmp (char const*,char const*,int) ; 

__attribute__((used)) static bool match_property(const char *a, const char *b)
{
    if (strcmp(a, "*") == 0)
        return true;
    // Give options and properties the same ID each, so change notifications
    // work both way.
    if (strncmp(a, "options/", 8) == 0)
        a += 8;
    if (strncmp(b, "options/", 8) == 0)
        b += 8;
    int len_a = prefix_len(a);
    int len_b = prefix_len(b);
    return strncmp(a, b, MPMIN(len_a, len_b)) == 0;
}