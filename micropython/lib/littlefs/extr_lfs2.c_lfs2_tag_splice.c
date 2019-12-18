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
typedef  int /*<<< orphan*/  lfs2_tag_t ;
typedef  int /*<<< orphan*/  int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  lfs2_tag_chunk (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int8_t lfs2_tag_splice(lfs2_tag_t tag) {
    return (int8_t)lfs2_tag_chunk(tag);
}