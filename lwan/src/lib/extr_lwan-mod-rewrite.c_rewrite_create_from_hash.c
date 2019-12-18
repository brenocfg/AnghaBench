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
struct hash {int dummy; } ;

/* Variables and functions */
 void* rewrite_create (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *rewrite_create_from_hash(const char *prefix,
                                      const struct hash *hash
                                      __attribute__((unused)))
{
    return rewrite_create(prefix, NULL);
}