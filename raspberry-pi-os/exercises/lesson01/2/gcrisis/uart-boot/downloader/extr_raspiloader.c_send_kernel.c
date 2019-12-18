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
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int ssize_t ;
typedef  int off_t ;

/* Variables and functions */
 int BUF_SIZE ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  do_exit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ htole32 (int) ; 
 int lseek (int,long,int /*<<< orphan*/ ) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char const*) ; 
 int /*<<< orphan*/  printf (char*,char const*,size_t) ; 
 int read (int,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  tcdrain (int) ; 
 int write (int,char*,int) ; 

void send_kernel(int fd, const char *file) {
    int file_fd;
    off_t off;
    uint32_t size;
    ssize_t pos;
    char *p;
    bool done = false;

    // Open file
    if ((file_fd = open(file, O_RDONLY)) == -1) {
        perror(file);
        do_exit(fd, EXIT_FAILURE);
    }

    // Get kernel size
    off = lseek(file_fd, 0L, SEEK_END);
    if (off > 0x200000) {
        fprintf(stderr, "kernel too big\n");
        do_exit(fd, EXIT_FAILURE);
    }
    size = htole32(off);
    lseek(file_fd, 0L, SEEK_SET);

    printf("### sending kernel %s [%zu byte]\n", file, (size_t)off);

    // send kernel size to RPi
    p = (uint8_t*)&size;
    pos = 0;   
    while(pos < 4) 
    {
        ssize_t len = write(fd, &p[pos], 4 - pos);
        	tcdrain(fd);
        if (len == -1) {
            perror("write()");
            do_exit(fd, EXIT_FAILURE);
        }
        pos += len;
    }
    //check size
    uint8_t sizee[4]={0};
    pos=0;
    while(pos<4){
    int nn=read(fd, sizee, 4-pos);
        pos+=nn;
    }
    uint32_t size_check=sizee[0]<<24|sizee[1]<<16|sizee[2]<<8|sizee[3];
    if(size_check!=size)
    {
        perror("size check error");
        do_exit(fd, EXIT_FAILURE);
    }
    while(!done)
    {
        char buf[BUF_SIZE];
        ssize_t pos = 0;
        ssize_t len = read(file_fd, buf, BUF_SIZE);
        switch(len) {
        case -1:
            perror("read()");
            do_exit(fd, EXIT_FAILURE);
        case 0:
            done = true;
        }
        
        while(len > 0) 
        {
            ssize_t len2 = write(fd, &buf[pos], len);
            
            tcdrain(fd);        
            
            if (len2 == -1) {
            perror("write()");
            do_exit(fd, EXIT_FAILURE);
            }
            len -= len2;
            pos += len2;
        }
    }
    fprintf(stderr, "### finished sending\n");

    return;
}