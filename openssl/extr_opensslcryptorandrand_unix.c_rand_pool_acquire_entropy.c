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
typedef  int /*<<< orphan*/  RAND_POOL ;

/* Variables and functions */
 size_t rand_pool_entropy_available (int /*<<< orphan*/ *) ; 

size_t rand_pool_acquire_entropy(RAND_POOL *pool)
{
#  if defined(OPENSSL_RAND_SEED_NONE)
    return rand_pool_entropy_available(pool);
#  else
    size_t bytes_needed;
    size_t entropy_available = 0;
    unsigned char *buffer;

#   if defined(OPENSSL_RAND_SEED_GETRANDOM)
    {
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
    bytes_needed = rand_pool_bytes_needed(pool, 1 /*entropy_factor*/);
    {
        size_t i;
#ifdef DEVRANDOM_WAIT
        static int wait_done = 0;

        /*
         * On some implementations reading from /dev/urandom is possible
         * before it is initialized. Therefore we wait for /dev/random
         * to be readable to make sure /dev/urandom is initialized.
         */
        if (!wait_done && bytes_needed > 0) {
             int f = open(DEVRANDOM_WAIT, O_RDONLY);

             if (f >= 0) {
                 fd_set fds;

                 FD_ZERO(&fds);
                 FD_SET(f, &fds);
                 while (select(f+1, &fds, NULL, NULL, NULL) < 0
                        && errno == EINTR);
                 close(f);
             }
             wait_done = 1;
        }
#endif

        for (i = 0; bytes_needed > 0 && i < OSSL_NELEM(random_device_paths); i++) {
            ssize_t bytes = 0;
            /* Maximum allowed number of consecutive unsuccessful attempts */
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
                    attempts = 3; /* reset counter after successful attempt */
                } else if (bytes < 0 && errno != EINTR) {
                    break;
                }
            }
            if (bytes < 0 || !keep_random_devices_open)
                close_random_device(i);

            bytes_needed = rand_pool_bytes_needed(pool, 1 /*entropy_factor*/);
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
    bytes_needed = rand_pool_bytes_needed(pool, 1 /*entropy_factor*/);
    if (bytes_needed > 0) {
        static const char *paths[] = { DEVRANDOM_EGD, NULL };
        int i;

        for (i = 0; paths[i] != NULL; i++) {
            buffer = rand_pool_add_begin(pool, bytes_needed);
            if (buffer != NULL) {
                size_t bytes = 0;
                int num = RAND_query_egd_bytes(paths[i],
                                               buffer, (int)bytes_needed);
                if (num == (int)bytes_needed)
                    bytes = bytes_needed;

                rand_pool_add_end(pool, bytes, 8 * bytes);
                entropy_available = rand_pool_entropy_available(pool);
            }
            if (entropy_available > 0)
                return entropy_available;
        }
    }
#   endif

    return rand_pool_entropy_available(pool);
#  endif
}