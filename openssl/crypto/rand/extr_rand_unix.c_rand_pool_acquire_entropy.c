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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  RAND_POOL ;

/* Variables and functions */
#define  DEVRANDOM_EGD 128 
 scalar_t__ EINTR ; 
 size_t OSSL_NELEM (int /*<<< orphan*/ ) ; 
 int RAND_query_egd_bytes (char const*,unsigned char*,int) ; 
 int /*<<< orphan*/  close_random_device (size_t) ; 
 scalar_t__ errno ; 
 int get_random_device (size_t) ; 
 int /*<<< orphan*/  keep_random_devices_open ; 
 size_t rand_acquire_entropy_from_cpu (int /*<<< orphan*/ *) ; 
 size_t rand_acquire_entropy_from_tsc (int /*<<< orphan*/ *) ; 
 unsigned char* rand_pool_add_begin (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  rand_pool_add_end (int /*<<< orphan*/ *,size_t,int) ; 
 size_t rand_pool_bytes_needed (int /*<<< orphan*/ *,int) ; 
 size_t rand_pool_entropy_available (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  random_device_paths ; 
 int read (int const,unsigned char*,size_t) ; 
 int syscall_random (unsigned char*,size_t) ; 
 scalar_t__ wait_random_seeded () ; 

size_t rand_pool_acquire_entropy(RAND_POOL *pool)
{
#  if defined(OPENSSL_RAND_SEED_NONE)
    return rand_pool_entropy_available(pool);
#  else
    size_t entropy_available;

#   if defined(OPENSSL_RAND_SEED_GETRANDOM)
    {
        size_t bytes_needed;
        unsigned char *buffer;
        ssize_t bytes;
        /* Maximum allowed number of consecutive unsuccessful attempts */
        int attempts = 3;

        bytes_needed = rand_pool_bytes_needed(pool, 1 /*entropy_factor*/);
        while (bytes_needed != 0 && attempts-- > 0) {
            buffer = rand_pool_add_begin(pool, bytes_needed);
            bytes = syscall_random(buffer, bytes_needed);
            if (bytes > 0) {
                rand_pool_add_end(pool, bytes, 8 * bytes);
                bytes_needed -= bytes;
                attempts = 3; /* reset counter after successful attempt */
            } else if (bytes < 0 && errno != EINTR) {
                break;
            }
        }
    }
    entropy_available = rand_pool_entropy_available(pool);
    if (entropy_available > 0)
        return entropy_available;
#   endif

#   if defined(OPENSSL_RAND_SEED_LIBRANDOM)
    {
        /* Not yet implemented. */
    }
#   endif

#   if defined(OPENSSL_RAND_SEED_DEVRANDOM)
    if (wait_random_seeded()) {
        size_t bytes_needed;
        unsigned char *buffer;
        size_t i;

        bytes_needed = rand_pool_bytes_needed(pool, 1 /*entropy_factor*/);
        for (i = 0; bytes_needed > 0 && i < OSSL_NELEM(random_device_paths);
             i++) {
            ssize_t bytes = 0;
            /* Maximum number of consecutive unsuccessful attempts */
            int attempts = 3;
            const int fd = get_random_device(i);

            if (fd == -1)
                continue;

            while (bytes_needed != 0 && attempts-- > 0) {
                buffer = rand_pool_add_begin(pool, bytes_needed);
                bytes = read(fd, buffer, bytes_needed);

                if (bytes > 0) {
                    rand_pool_add_end(pool, bytes, 8 * bytes);
                    bytes_needed -= bytes;
                    attempts = 3; /* reset counter on successful attempt */
                } else if (bytes < 0 && errno != EINTR) {
                    break;
                }
            }
            if (bytes < 0 || !keep_random_devices_open)
                close_random_device(i);

            bytes_needed = rand_pool_bytes_needed(pool, 1);
        }
        entropy_available = rand_pool_entropy_available(pool);
        if (entropy_available > 0)
            return entropy_available;
    }
#   endif

#   if defined(OPENSSL_RAND_SEED_RDTSC)
    entropy_available = rand_acquire_entropy_from_tsc(pool);
    if (entropy_available > 0)
        return entropy_available;
#   endif

#   if defined(OPENSSL_RAND_SEED_RDCPU)
    entropy_available = rand_acquire_entropy_from_cpu(pool);
    if (entropy_available > 0)
        return entropy_available;
#   endif

#   if defined(OPENSSL_RAND_SEED_EGD)
    {
        static const char *paths[] = { DEVRANDOM_EGD, NULL };
        size_t bytes_needed;
        unsigned char *buffer;
        int i;

        bytes_needed = rand_pool_bytes_needed(pool, 1 /*entropy_factor*/);
        for (i = 0; bytes_needed > 0 && paths[i] != NULL; i++) {
            size_t bytes = 0;
            int num;

            buffer = rand_pool_add_begin(pool, bytes_needed);
            num = RAND_query_egd_bytes(paths[i],
                                       buffer, (int)bytes_needed);
            if (num == (int)bytes_needed)
                bytes = bytes_needed;

            rand_pool_add_end(pool, bytes, 8 * bytes);
            bytes_needed = rand_pool_bytes_needed(pool, 1);
        }
        entropy_available = rand_pool_entropy_available(pool);
        if (entropy_available > 0)
            return entropy_available;
    }
#   endif

    return rand_pool_entropy_available(pool);
#  endif
}