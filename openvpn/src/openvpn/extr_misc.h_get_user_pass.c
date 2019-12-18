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
struct user_pass {int dummy; } ;

/* Variables and functions */
 int get_user_pass_cr (struct user_pass*,char const*,char const*,unsigned int const,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool
get_user_pass(struct user_pass *up,
              const char *auth_file,
              const char *prefix,
              const unsigned int flags)
{
    return get_user_pass_cr(up, auth_file, prefix, flags, NULL);
}