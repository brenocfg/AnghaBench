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
struct ecryptfs_msg_ctx {int dummy; } ;
struct ecryptfs_message {int dummy; } ;

/* Variables and functions */
 int ENOMSG ; 

__attribute__((used)) static inline int ecryptfs_wait_for_response(struct ecryptfs_msg_ctx *msg_ctx,
					     struct ecryptfs_message **emsg)
{
	return -ENOMSG;
}