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
struct termios {int c_cflag; scalar_t__ c_lflag; scalar_t__ c_oflag; scalar_t__ c_iflag; scalar_t__* c_cc; } ;

/* Variables and functions */
 int /*<<< orphan*/  B115200 ; 
 int CLOCAL ; 
 int CREAD ; 
 int CS8 ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int O_NOCTTY ; 
 int O_RDWR ; 
 int /*<<< orphan*/  TCSAFLUSH ; 
 size_t VMIN ; 
 size_t VTIME ; 
 scalar_t__ cfsetispeed (struct termios*,int /*<<< orphan*/ ) ; 
 scalar_t__ cfsetospeed (struct termios*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_exit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  isatty (int) ; 
 int open (char const*,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int tcgetattr (int,struct termios*) ; 
 int tcsetattr (int,int /*<<< orphan*/ ,struct termios*) ; 

int open_serial(const char *dev) {
    
    struct termios termios;
    int fd = open(dev, O_RDWR | O_NOCTTY);
    printf("fd=%d\r\n",fd);
    if (fd == -1) 
    {
    // failed to open
        return -1;
    }
    // must be a tty
    if (!isatty(fd))
    {
        fprintf(stderr, "%s is not a tty\n", dev);
        do_exit(fd, EXIT_FAILURE);
    }

    // Get the attributes.
    if(tcgetattr(fd, &termios) == -1)
    {
        perror("Failed to get attributes of device");
        do_exit(fd, EXIT_FAILURE);
    }
    // So, we poll.
    termios.c_cc[VTIME] = 0;
    termios.c_cc[VMIN] = 0;

    // 8N1 mode, no input/output/line processing masks.
    termios.c_iflag = 0;
    termios.c_oflag = 0;
    termios.c_cflag = CS8 | CREAD | CLOCAL;
    termios.c_lflag = 0;

    // Set the baud rate.
    if((cfsetispeed(&termios, B115200) < 0) ||
       (cfsetospeed(&termios, B115200) < 0))
    {
        perror("Failed to set baud-rate");
        do_exit(fd, EXIT_FAILURE);
    }

    // Write the attributes.
    if (tcsetattr(fd, TCSAFLUSH, &termios) == -1) {
        perror("tcsetattr()");
        do_exit(fd, EXIT_FAILURE);
    }
    return fd;
}