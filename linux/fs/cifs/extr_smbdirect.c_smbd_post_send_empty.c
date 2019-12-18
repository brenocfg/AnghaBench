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
struct smbd_connection {int /*<<< orphan*/  count_send_empty; } ;

/* Variables and functions */
 int smbd_post_send_sgl (struct smbd_connection*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smbd_post_send_empty(struct smbd_connection *info)
{
	info->count_send_empty++;
	return smbd_post_send_sgl(info, NULL, 0, 0);
}