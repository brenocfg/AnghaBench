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
 char* strip_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strip_start (char*) ; 

__attribute__((used)) static char *strip_ends(char *name)
{
    return strip_end(strip_start(name));
}