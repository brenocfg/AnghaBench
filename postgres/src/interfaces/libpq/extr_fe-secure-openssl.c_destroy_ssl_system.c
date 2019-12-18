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

/* Variables and functions */
 scalar_t__ CRYPTO_get_id_callback () ; 
 scalar_t__ CRYPTO_get_locking_callback () ; 
 int /*<<< orphan*/  CRYPTO_set_id_callback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRYPTO_set_locking_callback (int /*<<< orphan*/ *) ; 
 scalar_t__ pq_init_crypto_lib ; 
 scalar_t__ pq_lockingcallback ; 
 scalar_t__ pq_threadidcallback ; 
 scalar_t__ pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssl_config_mutex ; 
 scalar_t__ ssl_open_connections ; 

__attribute__((used)) static void
destroy_ssl_system(void)
{
#if defined(ENABLE_THREAD_SAFETY) && defined(HAVE_CRYPTO_LOCK)
	/* Mutex is created in pgtls_init() */
	if (pthread_mutex_lock(&ssl_config_mutex))
		return;

	if (pq_init_crypto_lib && ssl_open_connections > 0)
		--ssl_open_connections;

	if (pq_init_crypto_lib && ssl_open_connections == 0)
	{
		/*
		 * No connections left, unregister libcrypto callbacks, if no one
		 * registered different ones in the meantime.
		 */
		if (CRYPTO_get_locking_callback() == pq_lockingcallback)
			CRYPTO_set_locking_callback(NULL);
		if (CRYPTO_get_id_callback() == pq_threadidcallback)
			CRYPTO_set_id_callback(NULL);

		/*
		 * We don't free the lock array. If we get another connection in this
		 * process, we will just re-use them with the existing mutexes.
		 *
		 * This means we leak a little memory on repeated load/unload of the
		 * library.
		 */
	}

	pthread_mutex_unlock(&ssl_config_mutex);
#endif
}