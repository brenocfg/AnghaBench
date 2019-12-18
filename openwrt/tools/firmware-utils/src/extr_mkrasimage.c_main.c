#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {void* name; } ;
struct TYPE_7__ {void* name; } ;
struct TYPE_6__ {scalar_t__ size; void* name; } ;
struct TYPE_5__ {scalar_t__ size; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  basename (char*) ; 
 void* board_name ; 
 int build_image () ; 
 int check_options () ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ header_length ; 
 TYPE_4__ kernel ; 
 void* optarg ; 
 TYPE_3__ out ; 
 int /*<<< orphan*/  progname ; 
 TYPE_2__ rootfs ; 
 TYPE_1__ rootfs_out ; 
 scalar_t__ rootfs_size ; 
 int /*<<< orphan*/  sscanf (void*,char*,scalar_t__*) ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 
 void* version_name ; 

int main(int argc, char *argv[])
{
    int ret;
    progname = basename(argv[0]);
    while (1) {
        int c;

        c = getopt(argc, argv, "b:k:o:r:s:v:l:h");
        if (c == -1)
            break;

        switch (c) {
            case 'b':
                board_name = optarg;
                break;
            case 'h':
                usage(EXIT_SUCCESS);
                break;
            case 'k':
                kernel.name = optarg;
                break;
            case 'o':
                out.name = optarg;
                break;
            case 'r':
                rootfs.name = optarg;
                break;
            case 's':
                sscanf(optarg, "%u", &rootfs_size);
                break;
            case 'v':
                version_name = optarg;
                break;
            case 'l':
                sscanf(optarg, "%u", &header_length);
                break;
            default:
                usage(EXIT_FAILURE);
                break;
        }
    }

    ret = check_options();
    if (ret)
        usage(EXIT_FAILURE);

    /* As ZyXEL Web-GUI only accept images with a rootfs equal or larger than the first firmware shipped
     * for the device, we need to pad rootfs partition to this size. To perform further calculations, we
     * decide the size of this part here. In case the rootfs we want to integrate in our image is larger,
     * take it's size, otherwise the supplied size.
     *
     * Be careful! We rely on assertion of correct size to be performed beforehand. It is unknown if images
     * with a to large rootfs are accepted or not.
     */
    rootfs_out.size = rootfs_size < rootfs.size ? rootfs.size : rootfs_size;
    return build_image();
}