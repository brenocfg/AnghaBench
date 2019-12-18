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
struct file_info {int /*<<< orphan*/  size; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  KERNEL_HEADER_LEN ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 unsigned int htonl (int /*<<< orphan*/ ) ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,unsigned int*,int) ; 
 unsigned int zyxel_chksm (unsigned char const*,int /*<<< orphan*/ ) ; 

char *generate_kernel_header(struct file_info kernel)
{
    unsigned int chksm, size;
    char *kernel_header;
    size_t ptr = 0;

    kernel_header = malloc(KERNEL_HEADER_LEN);
    if (!kernel_header) {
        ERR("Couldn't allocate memory for kernel header!");
        exit(EXIT_FAILURE);
    }

    chksm = zyxel_chksm((const unsigned char *)kernel.data, kernel.size);
    size = htonl(kernel.size);

    /* 4 bytes:  checksum of the kernel image */
    memcpy(kernel_header + ptr, &chksm, 4);
    ptr += 4;

    /* 4 bytes:  length of the contained kernel image file (big endian) */
    memcpy(kernel_header + ptr, &size, 4);

    return kernel_header;
}