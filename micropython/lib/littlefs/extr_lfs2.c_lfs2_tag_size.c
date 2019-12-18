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
typedef  int lfs2_tag_t ;
typedef  int lfs2_size_t ;

/* Variables and functions */

__attribute__((used)) static inline lfs2_size_t lfs2_tag_size(lfs2_tag_t tag) {
    return tag & 0x000003ff;
}