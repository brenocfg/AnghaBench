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
struct nk_image {int dummy; } ;
struct file_group {int group; char const* name; struct nk_image* icon; } ;
typedef  enum file_groups { ____Placeholder_file_groups } file_groups ;

/* Variables and functions */

__attribute__((used)) static struct file_group
FILE_GROUP(enum file_groups group, const char *name, struct nk_image *icon)
{
    struct file_group fg;
    fg.group = group;
    fg.name = name;
    fg.icon = icon;
    return fg;
}