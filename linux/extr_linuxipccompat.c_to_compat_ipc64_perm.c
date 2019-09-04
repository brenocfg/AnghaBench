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
struct ipc64_perm {int /*<<< orphan*/  seq; int /*<<< orphan*/  mode; int /*<<< orphan*/  cgid; int /*<<< orphan*/  cuid; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  key; } ;
struct compat_ipc64_perm {int /*<<< orphan*/  seq; int /*<<< orphan*/  mode; int /*<<< orphan*/  cgid; int /*<<< orphan*/  cuid; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  key; } ;

/* Variables and functions */

void to_compat_ipc64_perm(struct compat_ipc64_perm *to, struct ipc64_perm *from)
{
	to->key = from->key;
	to->uid = from->uid;
	to->gid = from->gid;
	to->cuid = from->cuid;
	to->cgid = from->cgid;
	to->mode = from->mode;
	to->seq = from->seq;
}