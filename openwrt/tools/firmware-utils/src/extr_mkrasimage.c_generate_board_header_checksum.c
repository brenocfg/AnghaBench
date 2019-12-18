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
 size_t BOARD_NAME_LEN ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  HEADER_PARTITION_CALC_LENGTH ; 
 size_t ROOTFS_HEADER_LEN ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int,int /*<<< orphan*/ ) ; 
 size_t strlen (char*) ; 
 unsigned int zyxel_chksm (unsigned char const*,int /*<<< orphan*/ ) ; 

unsigned int generate_board_header_checksum(char *kernel_hdr, char *rootfs_hdr, char *boardname)
{
    char *board_hdr_tmp;
    unsigned int sum;
    size_t ptr = 0;

    /*
     * The checksum of the board header is calculated over the first 2048 bytes of
     * the header partition with the rootfs checksum used as a placeholder for then
     * board checksum we calculate in this step. The checksum gained from this step
     * is then used for the final board header partition.
     */

    board_hdr_tmp = malloc(HEADER_PARTITION_CALC_LENGTH);
    if (!board_hdr_tmp) {
        ERR("Couldn't allocate memory for temporary board header!");
        exit(EXIT_FAILURE);
    }
    memset(board_hdr_tmp, 0xff, HEADER_PARTITION_CALC_LENGTH);

    /* 40 bytes:  RootFS header */
    memcpy(board_hdr_tmp, rootfs_hdr, ROOTFS_HEADER_LEN);
    ptr += ROOTFS_HEADER_LEN;

    /* 4 bytes:  RootFS checksum (BE) as placeholder for board-header checksum */
    memcpy(board_hdr_tmp + ptr, rootfs_hdr, 4);
    ptr += 4;

    /* 32 bytes:  Model (e.g. "NBG6617", NUL termiated, 0xff padded) */
    memcpy(board_hdr_tmp + ptr, boardname, strlen(boardname));
    ptr += strlen(boardname);
    /* Add null-terminator */
    board_hdr_tmp[ptr] = 0x0;
    ptr = ROOTFS_HEADER_LEN + 4 + BOARD_NAME_LEN;

    /* 8 bytes:  Kernel header */
    if (kernel_hdr)
        memcpy(board_hdr_tmp + ptr, kernel_hdr, 8);

    /* Calculate the checksum over the first 2048 bytes */
    sum = zyxel_chksm((const unsigned char *)board_hdr_tmp, HEADER_PARTITION_CALC_LENGTH);
    free(board_hdr_tmp);
    return sum;
}