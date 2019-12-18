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
struct env_set {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CC_NAME ; 
 int /*<<< orphan*/  CC_PRINT ; 
 int /*<<< orphan*/  setenv_str_ex (struct env_set*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
setenv_str(struct env_set *es, const char *name, const char *value)
{
    setenv_str_ex(es, name, value, CC_NAME, 0, 0, CC_PRINT, 0, 0);
}