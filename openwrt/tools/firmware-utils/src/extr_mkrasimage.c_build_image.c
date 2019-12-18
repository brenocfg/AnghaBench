#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {char* data; int size; } ;
struct TYPE_11__ {char* data; int size; scalar_t__ name; } ;
struct TYPE_10__ {int size; char* data; } ;

/* Variables and functions */
 int BOARD_HEADER_LEN ; 
 int KERNEL_HEADER_LEN ; 
 int ROOTFS_HEADER_LEN ; 
 int /*<<< orphan*/  board_name ; 
 char* calloc (int,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* generate_board_header (char*,char*,int /*<<< orphan*/ ) ; 
 char* generate_kernel_header (TYPE_2__) ; 
 char* generate_rootfs_header (TYPE_3__,int /*<<< orphan*/ ) ; 
 size_t header_length ; 
 TYPE_2__ kernel ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  map_file (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 
 TYPE_1__ out ; 
 TYPE_2__ rootfs ; 
 TYPE_3__ rootfs_out ; 
 int /*<<< orphan*/  unmap_file (TYPE_2__*) ; 
 int /*<<< orphan*/  version_name ; 
 int /*<<< orphan*/  write_file (TYPE_1__*) ; 

int build_image()
{
    char *rootfs_header = NULL;
    char *kernel_header = NULL;
    char *board_header = NULL;

    size_t ptr;

    /* Load files */
    if (kernel.name)
        map_file(&kernel);
    map_file(&rootfs);

    /*
     * Allocate memory and copy input rootfs for temporary output rootfs.
     * This is important as we have to generate the rootfs checksum over the
     * entire rootfs partition. As we might have to pad the partition to allow
     * for flashing via ZyXEL's Web-GUI, we prepare the rootfs partition for the
     * output image here (and also use it for calculating the rootfs checksum).
     *
     * The roofs padding has to be done with 0x00.
     */
    rootfs_out.data = calloc(rootfs_out.size, sizeof(char));
    memcpy(rootfs_out.data, rootfs.data, rootfs.size);

    /* Prepare headers */
    rootfs_header = generate_rootfs_header(rootfs_out, version_name);
    if (kernel.name)
        kernel_header = generate_kernel_header(kernel);
    board_header = generate_board_header(kernel_header, rootfs_header, board_name);

    /* Prepare output file */
    out.size = header_length + rootfs_out.size;
    if (kernel.name)
        out.size += kernel.size;
    out.data = malloc(out.size);
    memset(out.data, 0xFF, out.size);

    /* Build output image */
    memcpy(out.data, rootfs_header, ROOTFS_HEADER_LEN);
    memcpy(out.data + ROOTFS_HEADER_LEN, board_header, BOARD_HEADER_LEN);
    if (kernel.name)
        memcpy(out.data + ROOTFS_HEADER_LEN + BOARD_HEADER_LEN, kernel_header, KERNEL_HEADER_LEN);
    ptr = header_length;
    memcpy(out.data + ptr, rootfs_out.data, rootfs_out.size);
    ptr += rootfs_out.size;
    if (kernel.name)
        memcpy(out.data + ptr, kernel.data, kernel.size);

    /* Write back output image */
    write_file(&out);

    /* Free allocated memory */
    if (kernel.name)
        unmap_file(&kernel);
    unmap_file(&rootfs);
    free(out.data);
    free(rootfs_out.data);

    free(rootfs_header);
    if (kernel.name)
        free(kernel_header);
    free(board_header);

    return 0;
}