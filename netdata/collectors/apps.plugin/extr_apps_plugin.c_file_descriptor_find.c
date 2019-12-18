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
typedef  scalar_t__ uint32_t ;
struct file_descriptor {char const* name; int magic; scalar_t__ pos; scalar_t__ count; scalar_t__ hash; } ;
typedef  int /*<<< orphan*/  avl ;

/* Variables and functions */
 int /*<<< orphan*/  all_files_index ; 
 scalar_t__ avl_search (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ simple_hash (char const*) ; 

__attribute__((used)) static struct file_descriptor *file_descriptor_find(const char *name, uint32_t hash) {
    struct file_descriptor tmp;
    tmp.hash = (hash)?hash:simple_hash(name);
    tmp.name = name;
    tmp.count = 0;
    tmp.pos = 0;
#ifdef NETDATA_INTERNAL_CHECKS
    tmp.magic = 0x0BADCAFE;
#endif /* NETDATA_INTERNAL_CHECKS */

    return (struct file_descriptor *)avl_search(&all_files_index, (avl *) &tmp);
}