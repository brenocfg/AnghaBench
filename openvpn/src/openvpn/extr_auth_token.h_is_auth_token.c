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
 int /*<<< orphan*/  SESSION_ID_PREFIX ; 
 scalar_t__ memcmp_constant_time (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
is_auth_token(const char *password)
{
    return (memcmp_constant_time(SESSION_ID_PREFIX, password,
                                 strlen(SESSION_ID_PREFIX)) == 0);
}