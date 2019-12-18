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
struct target {int target_fds_size; int /*<<< orphan*/ * target_fds; } ;

/* Variables and functions */
 int all_files_size ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * reallocz (int /*<<< orphan*/ *,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void reallocate_target_fds(struct target *w) {
    if(unlikely(!w))
        return;

    if(unlikely(!w->target_fds || w->target_fds_size < all_files_size)) {
        w->target_fds = reallocz(w->target_fds, sizeof(int) * all_files_size);
        memset(&w->target_fds[w->target_fds_size], 0, sizeof(int) * (all_files_size - w->target_fds_size));
        w->target_fds_size = all_files_size;
    }
}