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
struct section {char* name; scalar_t__ hash; } ;
struct config {int /*<<< orphan*/  index; } ;
typedef  int /*<<< orphan*/  avl ;

/* Variables and functions */
 scalar_t__ avl_search_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ simple_hash (char const*) ; 

__attribute__((used)) static struct section *appconfig_index_find(struct config *root, const char *name, uint32_t hash) {
    struct section tmp;
    tmp.hash = (hash)?hash:simple_hash(name);
    tmp.name = (char *)name;

    return (struct section *)avl_search_lock(&root->index, (avl *) &tmp);
}