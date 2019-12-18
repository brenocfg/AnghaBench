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
 int /*<<< orphan*/  OPENSSL_strlcpy (char*,char*,size_t) ; 
 char* strerror (int) ; 
 char* strerror_r (int,char*,size_t) ; 
 int /*<<< orphan*/  strerror_s (char*,size_t,int) ; 

int openssl_strerror_r(int errnum, char *buf, size_t buflen)
{
#if defined(_MSC_VER) && _MSC_VER>=1400
    return !strerror_s(buf, buflen, errnum);
#elif defined(_GNU_SOURCE)
    char *err;

    /*
     * GNU strerror_r may not actually set buf.
     * It can return a pointer to some (immutable) static string in which case
     * buf is left unused.
     */
    err = strerror_r(errnum, buf, buflen);
    if (err == NULL || buflen == 0)
        return 0;
    /*
     * If err is statically allocated, err != buf and we need to copy the data.
     * If err points somewhere inside buf, OPENSSL_strlcpy can handle this,
     * since src and dest are not annotated with __restrict and the function
     * reads src byte for byte and writes to dest.
     * If err == buf we do not have to copy anything.
     */
    if (err != buf)
        OPENSSL_strlcpy(buf, err, buflen);
    return 1;
#elif (defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE >= 200112L) || \
      (defined(_XOPEN_SOURCE) && _XOPEN_SOURCE >= 600)
    /*
     * We can use "real" strerror_r. The OpenSSL version differs in that it
     * gives 1 on success and 0 on failure for consistency with other OpenSSL
     * functions. Real strerror_r does it the other way around
     */
    return !strerror_r(errnum, buf, buflen);
#else
    char *err;

    /* Fall back to non-thread safe strerror()...its all we can do */
    if (buflen < 2)
        return 0;
    err = strerror(errnum);
    /* Can this ever happen? */
    if (err == NULL)
        return 0;
    OPENSSL_strlcpy(buf, err, buflen);
    return 1;
#endif
}