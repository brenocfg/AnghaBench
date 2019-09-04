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
 int /*<<< orphan*/  UNUSEDPARM (int) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void *my_null(int x, ...)
{
	UNUSEDPARM(x);
    printf("%.*s", 0, "a"); /* Remove warnings about no effects */
    return 0;
}