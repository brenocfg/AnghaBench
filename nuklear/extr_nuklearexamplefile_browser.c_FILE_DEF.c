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
struct file {int type; char const* suffix; int group; } ;
typedef  enum file_types { ____Placeholder_file_types } file_types ;
typedef  enum file_groups { ____Placeholder_file_groups } file_groups ;

/* Variables and functions */

__attribute__((used)) static struct file
FILE_DEF(enum file_types type, const char *suffix, enum file_groups group)
{
    struct file fd;
    fd.type = type;
    fd.suffix = suffix;
    fd.group = group;
    return fd;
}