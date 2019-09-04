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
typedef  int time_t ;
struct pollfd {int fd; int events; int revents; } ;
typedef  int int32_t ;
typedef  int fe_status_t ;
typedef  int /*<<< orphan*/  dvb_priv_t ;

/* Variables and functions */
 int FE_HAS_LOCK ; 
 int /*<<< orphan*/  FE_READ_BER ; 
 int /*<<< orphan*/  FE_READ_SIGNAL_STRENGTH ; 
 int /*<<< orphan*/  FE_READ_SNR ; 
 int /*<<< orphan*/  FE_READ_STATUS ; 
 int /*<<< orphan*/  FE_READ_UNCORRECTED_BLOCKS ; 
 int FE_TIMEDOUT ; 
 int /*<<< orphan*/  MP_ERR (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  MP_VERBOSE (int /*<<< orphan*/ *,char*,...) ; 
 int POLLPRI ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ poll (struct pollfd*,int,int) ; 
 int /*<<< orphan*/  print_status (int /*<<< orphan*/ *,int) ; 
 int time (int*) ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static int check_status(dvb_priv_t *priv, int fd_frontend, int tmout)
{
    int32_t strength;
    fe_status_t festatus;
    struct pollfd pfd[1];
    int ok = 0, locks = 0;
    time_t tm1, tm2;

    pfd[0].fd = fd_frontend;
    pfd[0].events = POLLPRI;

    MP_VERBOSE(priv, "Getting frontend status\n");
    tm1 = tm2 = time((time_t *) NULL);
    while (!ok) {
        festatus = 0;
        if (poll(pfd, 1, tmout * 1000) > 0) {
            if (pfd[0].revents & POLLPRI) {
                if (ioctl(fd_frontend, FE_READ_STATUS, &festatus) >= 0) {
                    if (festatus & FE_HAS_LOCK)
                        locks++;
                }
            }
        }
        usleep(10000);
        tm2 = time((time_t *) NULL);
        if ((festatus & FE_TIMEDOUT) || (locks >= 2) || (tm2 - tm1 >= tmout))
            ok = 1;
    }

    if (festatus & FE_HAS_LOCK) {
        strength = 0;
        if (ioctl(fd_frontend, FE_READ_BER, &strength) >= 0)
            MP_VERBOSE(priv, "Bit error rate: %d\n", strength);

        strength = 0;
        if (ioctl(fd_frontend, FE_READ_SIGNAL_STRENGTH, &strength) >= 0)
            MP_VERBOSE(priv, "Signal strength: %d\n", strength);

        strength = 0;
        if (ioctl(fd_frontend, FE_READ_SNR, &strength) >= 0)
            MP_VERBOSE(priv, "SNR: %d\n", strength);

        strength = 0;
        if (ioctl(fd_frontend, FE_READ_UNCORRECTED_BLOCKS, &strength) >= 0)
            MP_VERBOSE(priv, "UNC: %d\n", strength);

        print_status(priv, festatus);
    } else {
        MP_ERR(priv, "Not able to lock to the signal on the given frequency, "
               "timeout: %d\n", tmout);
        return -1;
    }
    return 0;
}