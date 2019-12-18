#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  avl ;
struct TYPE_2__ {int /*<<< orphan*/  registry_urls_root_index; } ;
typedef  int /*<<< orphan*/  REGISTRY_URL ;

/* Variables and functions */
 scalar_t__ avl_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__ registry ; 

inline REGISTRY_URL *registry_url_index_del(REGISTRY_URL *u) {
    return (REGISTRY_URL *)avl_remove(&(registry.registry_urls_root_index), (avl *)(u));
}