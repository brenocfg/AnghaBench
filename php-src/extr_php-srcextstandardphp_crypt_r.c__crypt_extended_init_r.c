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
typedef  scalar_t__ sig_atomic_t ;

/* Variables and functions */
 int /*<<< orphan*/  _crypt_extended_init () ; 

void _crypt_extended_init_r(void)
{
#ifdef PHP_WIN32
	LONG volatile initialized = 0;
#elif defined(HAVE_ATOMIC_H) /* Solaris 10 defines atomic API within */
	volatile unsigned int initialized = 0;
#else
	static volatile sig_atomic_t initialized = 0;
#endif

#ifdef ZTS
	tsrm_mutex_lock(php_crypt_extended_init_lock);
#endif

	if (!initialized) {
#ifdef PHP_WIN32
		InterlockedIncrement(&initialized);
#elif defined(HAVE_SYNC_FETCH_AND_ADD)
		__sync_fetch_and_add(&initialized, 1);
#elif defined(HAVE_ATOMIC_H) /* Solaris 10 defines atomic API within */
		membar_producer();
		atomic_add_int(&initialized, 1);
#endif
		_crypt_extended_init();
	}
#ifdef ZTS
	tsrm_mutex_unlock(php_crypt_extended_init_lock);
#endif
}