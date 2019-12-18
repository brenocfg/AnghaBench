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
struct envvars_map {scalar_t__ len; int /*<<< orphan*/  path; scalar_t__ var; } ;
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 scalar_t__ ExpandEnvironmentStringsW (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void init_envvars_map(struct envvars_map *map)
{
    while (map->var)
    {
        map->len = ExpandEnvironmentStringsW(map->var, map->path, sizeof(map->path)/sizeof(WCHAR));
        /* exclude null from length */
        if (map->len) map->len--;
        map++;
    }
}