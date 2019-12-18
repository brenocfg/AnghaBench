#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ lfs1_size_t ;
struct TYPE_4__ {scalar_t__ nlen; scalar_t__ alen; scalar_t__ elen; } ;
struct TYPE_5__ {TYPE_1__ d; } ;
typedef  TYPE_2__ lfs1_entry_t ;

/* Variables and functions */

__attribute__((used)) static inline lfs1_size_t lfs1_entry_size(const lfs1_entry_t *entry) {
    return 4 + entry->d.elen + entry->d.alen + entry->d.nlen;
}