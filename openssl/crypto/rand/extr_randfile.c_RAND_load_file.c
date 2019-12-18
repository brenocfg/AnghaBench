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
struct stat {long st_size; int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  ERR_add_error_data (int,char*,char const*) ; 
 int /*<<< orphan*/  OPENSSL_cleanse (unsigned char*,int) ; 
 int RAND_BUF_SIZE ; 
 long RAND_DRBG_STRENGTH ; 
 int /*<<< orphan*/  RAND_F_RAND_LOAD_FILE ; 
 int RAND_LOAD_BUF_SIZE ; 
 int /*<<< orphan*/  RAND_R_CANNOT_OPEN_FILE ; 
 int /*<<< orphan*/  RAND_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  RAND_R_RESEED_ERROR ; 
 int /*<<< orphan*/  RAND_add (unsigned char*,int,double) ; 
 int /*<<< orphan*/  RAND_status () ; 
 int /*<<< orphan*/  RANDerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clearerr (int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int fread (unsigned char*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ fstat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/ * openssl_fopen (char const*,char*) ; 
 int /*<<< orphan*/  setbuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int RAND_load_file(const char *file, long bytes)
{
    /*
     * The load buffer size exceeds the chunk size by the comfortable amount
     * of 'RAND_DRBG_STRENGTH' bytes (not bits!). This is done on purpose
     * to avoid calling RAND_add() with a small final chunk. Instead, such
     * a small final chunk will be added together with the previous chunk
     * (unless it's the only one).
     */
#define RAND_LOAD_BUF_SIZE (RAND_BUF_SIZE + RAND_DRBG_STRENGTH)
    unsigned char buf[RAND_LOAD_BUF_SIZE];

#ifndef OPENSSL_NO_POSIX_IO
    struct stat sb;
#endif
    int i, n, ret = 0;
    FILE *in;

    if (bytes == 0)
        return 0;

    if ((in = openssl_fopen(file, "rb")) == NULL) {
        RANDerr(RAND_F_RAND_LOAD_FILE, RAND_R_CANNOT_OPEN_FILE);
        ERR_add_error_data(2, "Filename=", file);
        return -1;
    }

#ifndef OPENSSL_NO_POSIX_IO
    if (fstat(fileno(in), &sb) < 0) {
        RANDerr(RAND_F_RAND_LOAD_FILE, RAND_R_INTERNAL_ERROR);
        ERR_add_error_data(2, "Filename=", file);
        fclose(in);
        return -1;
    }

    if (bytes < 0) {
        if (S_ISREG(sb.st_mode))
            bytes = sb.st_size;
        else
            bytes = RAND_DRBG_STRENGTH;
    }
#endif
    /*
     * On VMS, setbuf() will only take 32-bit pointers, and a compilation
     * with /POINTER_SIZE=64 will give off a MAYLOSEDATA2 warning here.
     * However, we trust that the C RTL will never give us a FILE pointer
     * above the first 4 GB of memory, so we simply turn off the warning
     * temporarily.
     */
#if defined(OPENSSL_SYS_VMS) && defined(__DECC)
# pragma environment save
# pragma message disable maylosedata2
#endif
    /*
     * Don't buffer, because even if |file| is regular file, we have
     * no control over the buffer, so why would we want a copy of its
     * contents lying around?
     */
    setbuf(in, NULL);
#if defined(OPENSSL_SYS_VMS) && defined(__DECC)
# pragma environment restore
#endif

    for ( ; ; ) {
        if (bytes > 0)
            n = (bytes <= RAND_LOAD_BUF_SIZE) ? (int)bytes : RAND_BUF_SIZE;
        else
            n = RAND_LOAD_BUF_SIZE;
        i = fread(buf, 1, n, in);
#ifdef EINTR
        if (ferror(in) && errno == EINTR){
            clearerr(in);
            if (i == 0)
                continue;
        }
#endif
        if (i == 0)
            break;

        RAND_add(buf, i, (double)i);
        ret += i;

        /* If given a bytecount, and we did it, break. */
        if (bytes > 0 && (bytes -= i) <= 0)
            break;
    }

    OPENSSL_cleanse(buf, sizeof(buf));
    fclose(in);
    if (!RAND_status()) {
        RANDerr(RAND_F_RAND_LOAD_FILE, RAND_R_RESEED_ERROR);
        ERR_add_error_data(2, "Filename=", file);
        return -1;
    }

    return ret;
}