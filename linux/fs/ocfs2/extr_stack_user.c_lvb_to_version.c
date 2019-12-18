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
struct ocfs2_protocol_version {int /*<<< orphan*/  pv_minor; int /*<<< orphan*/  pv_major; } ;

/* Variables and functions */

__attribute__((used)) static void lvb_to_version(char *lvb, struct ocfs2_protocol_version *ver)
{
	struct ocfs2_protocol_version *pv =
		(struct ocfs2_protocol_version *)lvb;
	/*
	 * ocfs2_protocol_version has two u8 variables, so we don't
	 * need any endian conversion.
	 */
	ver->pv_major = pv->pv_major;
	ver->pv_minor = pv->pv_minor;
}