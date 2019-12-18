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
typedef  int /*<<< orphan*/  uint8_t ;
struct lfs2_gstate {int /*<<< orphan*/  tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  lfs2_tag_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint8_t lfs2_gstate_getorphans(const struct lfs2_gstate *a) {
    return lfs2_tag_size(a->tag);
}