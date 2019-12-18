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
struct afs_cb_interest {int dummy; } ;
struct afs_call {int /*<<< orphan*/  cbi; } ;

/* Variables and functions */
 int /*<<< orphan*/  afs_get_cb_interest (struct afs_cb_interest*) ; 

__attribute__((used)) static inline void afs_use_fs_server(struct afs_call *call, struct afs_cb_interest *cbi)
{
	call->cbi = afs_get_cb_interest(cbi);
}