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
typedef  int /*<<< orphan*/  pthread_mutex_t ;
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 int /*<<< orphan*/ * CRYPTO_get_id_callback () ; 
 int /*<<< orphan*/ * CRYPTO_get_locking_callback () ; 
 int CRYPTO_num_locks () ; 
 int /*<<< orphan*/  CRYPTO_set_id_callback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_set_locking_callback (int /*<<< orphan*/ ) ; 
 int InterlockedExchange (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  OPENSSL_INIT_LOAD_CONFIG ; 
 int /*<<< orphan*/  OPENSSL_config (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_init_ssl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_library_init () ; 
 int /*<<< orphan*/  SSL_load_error_strings () ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ ** malloc (int) ; 
 scalar_t__ pq_init_crypto_lib ; 
 scalar_t__ pq_init_ssl_lib ; 
 int /*<<< orphan*/ ** pq_lockarray ; 
 int /*<<< orphan*/  pq_lockingcallback ; 
 int /*<<< orphan*/  pq_threadidcallback ; 
 scalar_t__ pthread_mutex_init (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_lock (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * ssl_config_mutex ; 
 int ssl_lib_initialized ; 
 int /*<<< orphan*/  ssl_open_connections ; 
 int /*<<< orphan*/  win32_ssl_create_mutex ; 

int
pgtls_init(PGconn *conn)
{
#ifdef ENABLE_THREAD_SAFETY
#ifdef WIN32
	/* Also see similar code in fe-connect.c, default_threadlock() */
	if (ssl_config_mutex == NULL)
	{
		while (InterlockedExchange(&win32_ssl_create_mutex, 1) == 1)
			 /* loop, another thread own the lock */ ;
		if (ssl_config_mutex == NULL)
		{
			if (pthread_mutex_init(&ssl_config_mutex, NULL))
				return -1;
		}
		InterlockedExchange(&win32_ssl_create_mutex, 0);
	}
#endif
	if (pthread_mutex_lock(&ssl_config_mutex))
		return -1;

#ifdef HAVE_CRYPTO_LOCK
	if (pq_init_crypto_lib)
	{
		/*
		 * If necessary, set up an array to hold locks for libcrypto.
		 * libcrypto will tell us how big to make this array.
		 */
		if (pq_lockarray == NULL)
		{
			int			i;

			pq_lockarray = malloc(sizeof(pthread_mutex_t) * CRYPTO_num_locks());
			if (!pq_lockarray)
			{
				pthread_mutex_unlock(&ssl_config_mutex);
				return -1;
			}
			for (i = 0; i < CRYPTO_num_locks(); i++)
			{
				if (pthread_mutex_init(&pq_lockarray[i], NULL))
				{
					free(pq_lockarray);
					pq_lockarray = NULL;
					pthread_mutex_unlock(&ssl_config_mutex);
					return -1;
				}
			}
		}

		if (ssl_open_connections++ == 0)
		{
			/*
			 * These are only required for threaded libcrypto applications,
			 * but make sure we don't stomp on them if they're already set.
			 */
			if (CRYPTO_get_id_callback() == NULL)
				CRYPTO_set_id_callback(pq_threadidcallback);
			if (CRYPTO_get_locking_callback() == NULL)
				CRYPTO_set_locking_callback(pq_lockingcallback);
		}
	}
#endif							/* HAVE_CRYPTO_LOCK */
#endif							/* ENABLE_THREAD_SAFETY */

	if (!ssl_lib_initialized)
	{
		if (pq_init_ssl_lib)
		{
#ifdef HAVE_OPENSSL_INIT_SSL
			OPENSSL_init_ssl(OPENSSL_INIT_LOAD_CONFIG, NULL);
#else
			OPENSSL_config(NULL);
			SSL_library_init();
			SSL_load_error_strings();
#endif
		}
		ssl_lib_initialized = true;
	}

#ifdef ENABLE_THREAD_SAFETY
	pthread_mutex_unlock(&ssl_config_mutex);
#endif
	return 0;
}