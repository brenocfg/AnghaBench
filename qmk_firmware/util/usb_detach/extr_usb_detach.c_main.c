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
struct usbdevfs_ioctl {int ifno; int /*<<< orphan*/ * data; int /*<<< orphan*/  ioctl_code; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  USBDEVFS_DISCONNECT ; 
 int /*<<< orphan*/  USBDEVFS_IOCTL ; 
 int ioctl (int,int /*<<< orphan*/ ,struct usbdevfs_ioctl*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int main(int argc, char**argv)
{
        struct usbdevfs_ioctl command;
        int ret;
        int fd;
        int i;
        if (argc>1) {
                fd = open(argv[1],O_RDWR);
                if (fd<1){
                        perror("unable to open file");
                        return 1;
                }
                for (i=0;i<255;i++){ // hack: should fetch how many interface there is.
                        command.ifno = i;
                        command.ioctl_code = USBDEVFS_DISCONNECT;
                        command.data = NULL;
                        ret = ioctl(fd, USBDEVFS_IOCTL, &command);
                        if(ret!=-1)
                                printf("un claimed interface %d %d\n",i,ret);
                }
        } else {
                printf ("usage: %s /dev/bus/usb/BUS/DEVICE\n",argv[0]);
                printf("Release all interfaces of this usb device for usage in virtualisation\n");
        }
}