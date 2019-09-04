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

/* Variables and functions */
 int ENOTCONN ; 

__attribute__((used)) static inline int ecryptfs_send_message(char *data, int data_len,
					struct ecryptfs_msg_ctx **msg_ctx)
{
	return -ENOTCONN;
}