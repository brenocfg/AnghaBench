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
typedef  int /*<<< orphan*/  value ;

/* Variables and functions */
 unsigned int DEFAULT_ODD_CONSTANT ; 
 int O_CLOEXEC ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  SYS_getrandom ; 
 int /*<<< orphan*/  close (int) ; 
 int getentropy (unsigned int*,int) ; 
 int open (char*,int) ; 
 int read (int,unsigned int*,int) ; 
 long syscall (int /*<<< orphan*/ ,unsigned int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int get_random_unsigned(void)
{
    unsigned int value;

#if defined(SYS_getrandom)
    long int ret = syscall(SYS_getrandom, &value, sizeof(value), 0);
    if (ret == sizeof(value))
        return value;
#elif defined(HAVE_GETENTROPY)
    int ret = getentropy(&value, sizeof(value));
    if (ret == 0)
        return value;
#endif

    int fd = open("/dev/urandom", O_CLOEXEC | O_RDONLY);
    if (fd < 0) {
        fd = open("/dev/random", O_CLOEXEC | O_RDONLY);
        if (fd < 0)
            return DEFAULT_ODD_CONSTANT;
    }
    if (read(fd, &value, sizeof(value)) != sizeof(value))
        value = DEFAULT_ODD_CONSTANT;
    close(fd);

    return value;
}