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
struct upid {int dummy; } ;
struct pid {int dummy; } ;
struct kmem_cache {int dummy; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 struct kmem_cache* READ_ONCE (struct kmem_cache*) ; 
 int /*<<< orphan*/  SLAB_HWCACHE_ALIGN ; 
 struct kmem_cache* kmem_cache_create (char*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct kmem_cache** pid_cache ; 
 int /*<<< orphan*/  pid_caches_mutex ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 

__attribute__((used)) static struct kmem_cache *create_pid_cachep(unsigned int level)
{
	/* Level 0 is init_pid_ns.pid_cachep */
	struct kmem_cache **pkc = &pid_cache[level - 1];
	struct kmem_cache *kc;
	char name[4 + 10 + 1];
	unsigned int len;

	kc = READ_ONCE(*pkc);
	if (kc)
		return kc;

	snprintf(name, sizeof(name), "pid_%u", level + 1);
	len = sizeof(struct pid) + level * sizeof(struct upid);
	mutex_lock(&pid_caches_mutex);
	/* Name collision forces to do allocation under mutex. */
	if (!*pkc)
		*pkc = kmem_cache_create(name, len, 0, SLAB_HWCACHE_ALIGN, 0);
	mutex_unlock(&pid_caches_mutex);
	/* current can fail, but someone else can succeed. */
	return READ_ONCE(*pkc);
}