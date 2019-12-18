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
struct decl_info {int dummy; } ;
struct signal_info {int signalling; struct decl_info func; int /*<<< orphan*/  mutex; int /*<<< orphan*/  callbacks; int /*<<< orphan*/ * next; } ;
typedef  int /*<<< orphan*/  pthread_mutexattr_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  PTHREAD_MUTEX_RECURSIVE ; 
 int /*<<< orphan*/  bfree (struct signal_info*) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 struct signal_info* bmalloc (int) ; 
 int /*<<< orphan*/  da_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decl_info_free (struct decl_info*) ; 
 scalar_t__ pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutexattr_init (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutexattr_settype (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct signal_info *signal_info_create(struct decl_info *info)
{
	pthread_mutexattr_t attr;
	struct signal_info *si;

	if (pthread_mutexattr_init(&attr) != 0)
		return NULL;
	if (pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE) != 0)
		return NULL;

	si = bmalloc(sizeof(struct signal_info));

	si->func = *info;
	si->next = NULL;
	si->signalling = false;
	da_init(si->callbacks);

	if (pthread_mutex_init(&si->mutex, &attr) != 0) {
		blog(LOG_ERROR, "Could not create signal");

		decl_info_free(&si->func);
		bfree(si);
		return NULL;
	}

	return si;
}