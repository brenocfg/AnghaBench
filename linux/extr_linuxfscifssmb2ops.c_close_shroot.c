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
struct cached_fid {int /*<<< orphan*/  fid_mutex; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smb2_close_cached_fid ; 

void close_shroot(struct cached_fid *cfid)
{
	mutex_lock(&cfid->fid_mutex);
	kref_put(&cfid->refcount, smb2_close_cached_fid);
	mutex_unlock(&cfid->fid_mutex);
}