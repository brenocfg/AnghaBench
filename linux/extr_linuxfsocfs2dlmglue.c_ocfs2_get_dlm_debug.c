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
struct ocfs2_dlm_debug {int /*<<< orphan*/  d_refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ocfs2_get_dlm_debug(struct ocfs2_dlm_debug *debug)
{
	kref_get(&debug->d_refcnt);
}