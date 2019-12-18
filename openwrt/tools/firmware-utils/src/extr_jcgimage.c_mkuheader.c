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
typedef  long uLong ;
struct uimage_header {int ih_os; int ih_arch; int ih_type; int ih_comp; void* ih_hcrc; void* ih_dcrc; void* ih_size; scalar_t__ ih_name; void* ih_fsoff; void* ih_ep; void* ih_load; void* ih_time; void* ih_magic; } ;

/* Variables and functions */
 long IH_MAGIC ; 
 void* Z_NULL ; 
 long crc32 (long,void*,int) ; 
 void* htonl (long) ; 
 int /*<<< orphan*/  memset (struct uimage_header*,int /*<<< orphan*/ ,int) ; 
 int ntohl (void*) ; 
 int /*<<< orphan*/  printf (char*,long) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 long time (int /*<<< orphan*/ *) ; 

void
mkuheader(struct uimage_header *h, size_t ksize, size_t fsize)
{
	uLong crc;
	void *payload = (void *)h + sizeof(*h);

	// printf("mkuheader: %p, %zd, %zd\n", h, ksize, fsize);
	memset(h, 0, sizeof(*h));
	h->ih_magic = htonl(IH_MAGIC);
	h->ih_time  = htonl(time(NULL));
	h->ih_size  = htonl(ksize + fsize);
	h->ih_load  = htonl(0x80000000);
	h->ih_ep    = htonl(0x80292000);
	h->ih_os    = 0x05;
	h->ih_arch  = 0x05;
	h->ih_type  = 0x02;
	h->ih_comp  = 0x03;
	h->ih_fsoff = htonl(sizeof(*h) + ksize);
	strcpy((char *)h->ih_name, "Linux Kernel Image");

	/* CRC over uImage payload (kernel and file system) */
	crc = crc32(0L, Z_NULL, 0);
	crc = crc32(crc, payload, ntohl(h->ih_size));
	h->ih_dcrc  = htonl(crc);
	printf("CRC1: %08lx\n", crc);

	/* CRC over uImage header */
	crc = crc32(0L, Z_NULL, 0);
	crc = crc32(crc, (void *)h, sizeof(*h));
	h->ih_hcrc  = htonl(crc);
	printf("CRC2: %08lx\n", crc);
}