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
 int /*<<< orphan*/  ERR_new () ; 
 int /*<<< orphan*/  ERR_set_debug (char const*,int,char const*) ; 
 int /*<<< orphan*/  ERR_set_error (int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void put_error(int lib, const char *func, int reason,
                      const char *file, int line)
{
    ERR_new();
    ERR_set_debug(file, line, func);
    ERR_set_error(lib, reason, NULL /* no data here, so fmt is NULL */);
}