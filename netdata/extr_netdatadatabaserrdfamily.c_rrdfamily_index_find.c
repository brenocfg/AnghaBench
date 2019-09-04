#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  avl ;
struct TYPE_6__ {char const* family; scalar_t__ hash_family; } ;
struct TYPE_5__ {int /*<<< orphan*/  rrdfamily_root_index; } ;
typedef  TYPE_1__ RRDHOST ;
typedef  TYPE_2__ RRDFAMILY ;

/* Variables and functions */
 scalar_t__ avl_search_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ simple_hash (char const*) ; 

__attribute__((used)) static RRDFAMILY *rrdfamily_index_find(RRDHOST *host, const char *id, uint32_t hash) {
    RRDFAMILY tmp;
    tmp.family = id;
    tmp.hash_family = (hash)?hash:simple_hash(tmp.family);

    return (RRDFAMILY *)avl_search_lock(&(host->rrdfamily_root_index), (avl *) &tmp);
}