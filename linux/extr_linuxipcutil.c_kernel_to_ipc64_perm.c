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
struct kern_ipc_perm {int /*<<< orphan*/  seq; int /*<<< orphan*/  mode; int /*<<< orphan*/  cgid; int /*<<< orphan*/  cuid; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  key; } ;
struct ipc64_perm {int /*<<< orphan*/  seq; int /*<<< orphan*/  mode; void* cgid; void* cuid; void* gid; void* uid; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  current_user_ns () ; 
 void* from_kgid_munged (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* from_kuid_munged (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void kernel_to_ipc64_perm(struct kern_ipc_perm *in, struct ipc64_perm *out)
{
	out->key	= in->key;
	out->uid	= from_kuid_munged(current_user_ns(), in->uid);
	out->gid	= from_kgid_munged(current_user_ns(), in->gid);
	out->cuid	= from_kuid_munged(current_user_ns(), in->cuid);
	out->cgid	= from_kgid_munged(current_user_ns(), in->cgid);
	out->mode	= in->mode;
	out->seq	= in->seq;
}